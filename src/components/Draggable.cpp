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
	boxDefinition = bd;
}

void Draggable::onMouse(Mouse* m)
{
	mouse = m;
	mouse->mousePress.connect<Draggable, &Draggable::onMousePress>(this);
}

void Draggable::onMouseDrag(float mouseX, float mouseY, int button)
{

}

void Draggable::onMousePress(float mouseX, float mouseY, int button)
{
	cout << "HELLO" << endl;
}

}
}// end namespace



