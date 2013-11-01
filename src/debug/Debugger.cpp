#include "Debugger.h"
#include "components/Mouse.h"
#include "components/Draw.h"

namespace boxModel {

namespace debug {

Debugger::Debugger() {
	addChild(&panel);
	flush();
}

Debugger::~Debugger() {
}

std::string Debugger::getType() {
	return "debugger";
}

void Debugger::setComponent(core::Component* component) {
	setComponentContainer(component->components);
}

void Debugger::setComponentContainer(core::ComponentContainer* c) {
	rootContainer = c;

	if(rootContainer->hasComponent<components::Draw>()) {
		rootContainer->getComponent<components::Draw>()->postDraw.connect<Draw, &Draw::draw>(this);
	}

	//route mouse events
	if(rootContainer->hasComponent<components::Mouse>()) {
		components::Mouse* m = rootContainer->getComponent<components::Mouse>();
		m->routeMouse(this, true);
	}

	boxConstrainer = new boxModel::tools::BoxConstrainer(rootContainer->getComponent<boxModel::components::BoxDefinition>(), this);
}

void Debugger::onMouseClick(float mouseX, float mouseY, int button) {
	if(rootContainer->hasComponent<Stack>()) {
		boxModel::components::Stack* childStack = rootContainer->getComponent<Stack>();
		core::ComponentContainer* container = childStack->containerAt(mouseX, mouseY);
		if(container == NULL)
			return;

		panel.showInfo(container);
	}
}

void Debugger::onMouseMove(float mouseX, float mouseY) {

}

void Debugger::onMouseMoveOutside(float mouseX, float mouseY) {
}

void Debugger::preDraw() {
	//containerOverlay.draw();
	cout << "pre draw " << endl;
}

}
} // end namespace
