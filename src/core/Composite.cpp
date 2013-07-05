#include "Composite.h"

using namespace boxModel::core;

Composite::Composite() {
	addComponent<boxModel::components::Stack>(this);
	addComponent<boxModel::components::Addressable>(this);
}

void Composite::flush() {
	for(unsigned int i = 0; i < getNumChildren(); i++){
		Composite* child = getChild<Composite>(i);
		if(child != NULL)
			child->flush();
	}
	
	for(unsigned int i = 0; i < getNumComponents(); i++){
		getComponent(i)->onFlush();
	}
}

Composite* Composite::clone()
{
	return clone<Composite>();
}
