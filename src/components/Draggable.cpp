#include "Draggable.h"

namespace boxModel {

namespace components {

Draggable::Draggable() {
}

Draggable::~Draggable() {
}

std::string Draggable::getName() {
	return "draggable";
}

void Draggable::setup()
{
	LISTEN_FOR_COMPONENT(Mouse, Draggable, onMouse)
	LISTEN_FOR_COMPONENT(BoxDefinition, Draggable, onBoxDefinition)
}

void Draggable::onBoxDefinition(BoxDefinition* bd)
{
}

void Draggable::onMouse(Mouse* m)
{
}


}
}// end namespace

