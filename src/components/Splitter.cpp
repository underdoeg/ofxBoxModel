#include "Splitter.h"

using namespace boxModel::core;
using namespace boxModel::components;
using namespace std;

void Splitter::setup()
{
	hasSplit = false;
	boxDefinition = NULL;
	LISTEN_FOR_COMPONENT(BoxDefinition, Splitter, onBoxDefinition)
	LISTEN_FOR_COMPONENT(Box, Splitter, onBox)
	LISTEN_FOR_COMPONENT(Stack, Splitter, onStack)
}

void Splitter::onBoxDefinition(BoxDefinition* bd)
{
	boxDefinition = bd;
}

void Splitter::onBox(Box* b)
{
	box = b;
}

void Splitter::onStack(Stack* s)
{
	stack = s;
}

void Splitter::onFlush()
{
}

std::vector<ComponentContainer*> Splitter::makeSplit()
{
	if(!hasSplit){
		merge();
		splits.clear();
		ComponentContainer* split1 = components->clone();
		ComponentContainer* split2 = components->clone();
		
		if(stack != NULL){
			//stack->removeFromParent();
		}
		
		if(boxDefinition != NULL && box != NULL){
			float splitHeight = box->size.y - splitPosition.y;
			split1->getComponent<BoxDefinition>()->height = splitPosition.y;
			split1->getComponent<BoxDefinition>()->height = Unit::Pixel;
			
			split2->getComponent<BoxDefinition>()->height = Unit::Pixel;
			split2->getComponent<BoxDefinition>()->height = splitHeight;
		}
		
		splits.push_back(split1);
		splits.push_back(split2);
		hasSplit = true;
		
		/*
		if(boxDefinition != NULL && box != NULL){
			
			
			originalWidth = boxDefinition->width;
			originalHeight = boxDefinition->height;
			boxDefinition->height = splitPosition.y;
			boxDefinition->height = Unit::Pixel;
			
			BoxDefinition* boxDefSplit = split->getComponent<BoxDefinition>();
			boxDefSplit->height = Unit::Pixel;
			boxDefSplit->height = splitHeight;
		}
		curSplitStatus = true;
		if(split->hasComponent<Addressable>()){
			split->getComponent<Addressable>()->unaddressable = true;
		}
		*/
	}
	return splits;
}

std::vector<ComponentContainer*> Splitter::getSplit()
{
	return splits;
}

bool Splitter::requestSplit(float x, float y)
{
	if(box != NULL){
		if(x != box->size.x){
			debug::warning("SPLITTING X OVERFLOW IS NOT SUPPORTED");
		}
	}
	splitPosition.set(x, y);
	hasSplit = false;
	splitRequested(x, y);
	return hasSplit;
}

void Splitter::merge()
{
	hasSplit = false;
	if(splits.size() != 2)
		return;
	delete splits[0];
	delete splits[1];
	splits.clear();
	//delete split;
}

bool Splitter::isSplitted()
{
	return hasSplit;
}
