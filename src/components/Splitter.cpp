#include "Splitter.h"

using namespace boxModel::core;
using namespace boxModel::components;
using namespace std;

void Splitter::setup()
{
	boxDefinition = NULL;
	LISTEN_FOR_COMPONENT(BoxDefinition, Splitter, onBoxDefinition)
	LISTEN_FOR_COMPONENT(Box, Splitter, onBox)
}

void Splitter::onBoxDefinition(BoxDefinition* bd)
{
	boxDefinition = bd;
}

void Splitter::onBox(Box* b)
{
	box = b;
}

void Splitter::onFlush()
{
}

ComponentContainer* Splitter::makeSplit()
{
	if(!curSplitStatus){
		split = components->clone();
		if(boxDefinition != NULL && box != NULL){
			float splitHeight = box->size.y - splitPosition.y;
			
			originalWidth = boxDefinition->width;
			originalHeight = boxDefinition->height;
			boxDefinition->height = splitPosition.y;
			boxDefinition->height = Unit::Pixel;
			
			BoxDefinition* boxDefSplit = split->getComponent<BoxDefinition>();
			boxDefSplit->height = Unit::Pixel;
			boxDefSplit->height = splitHeight;
		}
		curSplitStatus = true;
	}
	return split;
}

ComponentContainer* Splitter::getSplit()
{
	return split;
}

bool Splitter::requestSplit(float x, float y)
{
	if(box != NULL){
		if(x != box->size.x){
			debug::warning("SPLITTING X OVERFLOW IS NOT SUPPORTED");
		}
	}
	splitPosition.set(x, y);
	curSplitStatus = false;
	splitRequested(x, y);
	return curSplitStatus;
}