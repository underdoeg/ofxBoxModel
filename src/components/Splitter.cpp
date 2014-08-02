#include "Splitter.h"

using namespace boxModel::core;
using namespace boxModel::components;
using namespace std;

std::string Splitter::getName(){
	return "splitter";
}

void Splitter::setup() {
	hasSplits = false;
	isSplit = false;
	isSplitable = false;
	boxDefinition = NULL;
	LISTEN_FOR_COMPONENT(BoxModel, Splitter, onBoxDefinition)
	LISTEN_FOR_COMPONENT(BoxDefinition, Splitter, onBox)
	LISTEN_FOR_COMPONENT(Stack, Splitter, onStack)
}

void Splitter::onBoxDefinition(BoxModel* bd) {
	boxDefinition = bd;
}

void Splitter::onBox(BoxDefinition* b) {
	box = b;
}

void Splitter::onStack(Stack* s) {
	stack = s;
}

void Splitter::onFlush() {
}

void Splitter::markAsSplit(Splitter* s) {
	isSplit = true;
	splitter = s;
}

std::vector<ComponentContainer*> Splitter::makeSplit() {
	std::vector<ComponentContainer*> ret;
	if(!hasSplits) {
		float splitHeight = box->size.y - splitPosition.y;
		//if(!isSplit) {
		//merge();
		ComponentContainer* split1 = components->clone();
		split1->getComponent<Splitter>()->markAsSplit(this);
		ComponentContainer* split2 = components->clone();
		split2->getComponent<Splitter>()->markAsSplit(this);

		if(stack != NULL && stack->hasParent()) {
			//TODO: is this necessary?
			stack->getParent()->addChildContainer(split1);
			stack->getParent()->addChildContainer(split2);
		}

		if(boxDefinition != NULL && box != NULL) {
			split1->getComponent<BoxModel>()->height = splitPosition.y;
			split1->getComponent<BoxModel>()->height = Unit::Pixel;

			split2->getComponent<BoxModel>()->height = Unit::Pixel;
			split2->getComponent<BoxModel>()->height = splitHeight;
		}

		splits.push_back(split1);
		splits.push_back(split2);

		ret.push_back(split1);
		ret.push_back(split2);
		hasSplits = true;
	} else {
		//cout << "NO SPLIT!" << endl;
	}
	return ret;
}

std::vector<ComponentContainer*> Splitter::getSplits() {
	return splits;
}

bool Splitter::requestSplit(float x, float y) {
	
	if(!isSplitable)
		return false;
	
	if(box != NULL) {
		if(x != box->size.x) {
			//debug::warning("SPLITTING X OVERFLOW IS NOT SUPPORTED");
		}
	}
	splitPosition.set(x, y);
	hasSplits = false;
	splitRequested(x, y);
	return hasSplits;
}

void Splitter::merge() {
	if(hasSplits) {
		hasSplits = false;
		for(ComponentContainer* comp: splits) {
			delete comp;
		}
		splits.clear();
	}
}

void Splitter::getInfo(core::Component::Info& info){

}
