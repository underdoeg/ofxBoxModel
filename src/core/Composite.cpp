#include "Composite.h"

using namespace boxModel::core;

Composite::Composite() {
	addComponent<boxModel::components::Stack>(this);
	addComponent<boxModel::components::Addressable>(this);
}

void Composite::flush() {
	
}

Composite* Composite::clone()
{
	return clone<Composite>();
}
