#include "Debugger.h"
#include "components/Mouse.h"
#include "components/Draw.h"

namespace boxModel {

namespace debug {

Debugger::Debugger() {
	addChild(&overlayCurrent);
	addChild(&overlay);
	addChild(&panel);

	rootStack = NULL;
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

	rootContainer->postFlushed.connect<ComponentContainer, &ComponentContainer::flush>(this);

	if(rootContainer->hasComponent<components::Draw>()) {
		rootContainer->getComponent<components::Draw>()->postDraw.connect<Draw, &Draw::draw>(this);
	}

	onShow();

	if(rootContainer->hasComponent<components::Stack>())
		rootStack = rootContainer->getComponent<components::Stack>();

	boxConstrainer.set(rootContainer->getComponent<boxModel::components::BoxDefinition>(), this);
}

void Debugger::onMouseClick(float mouseX, float mouseY, int button) {
	if(rootStack == NULL)
		return;

	core::ComponentContainer* container = rootStack->containerAt(mouseX, mouseY);
	if(container == NULL)
		return;

	if(container->hasComponent<components::BoxDefinition>()) {
		components::BoxDefinition* boxDef = container->getComponent<components::BoxDefinition>();
		overlayCurrent.boxConstrainer.set(boxDef, &overlayCurrent, true);
	}

	panel.showInfo(container);
}

void Debugger::onMouseMove(float mouseX, float mouseY) {
	if(rootStack == NULL)
		return;

	core::ComponentContainer* container = rootStack->containerAt(mouseX, mouseY);
	if(container == NULL)
		return;

	if(container->hasComponent<components::BoxDefinition>()) {
		components::BoxDefinition* boxDef = container->getComponent<components::BoxDefinition>();
		overlay.boxConstrainer.set(boxDef, &overlay, true);
	}
}

void Debugger::onMouseMoveOutside(float mouseX, float mouseY) {
}

void boxModel::debug::Debugger::onHide() {
	//route mouse events
	if(rootContainer->hasComponent<components::Mouse>()) {
		components::Mouse* m = rootContainer->getComponent<components::Mouse>();
		m->removeRouteMouse();
	}
}

void boxModel::debug::Debugger::onShow() {
	//route mouse events
	if(rootContainer->hasComponent<components::Mouse>()) {
		components::Mouse* m = rootContainer->getComponent<components::Mouse>();
		m->routeMouse(this, true);
	}
}

}
} // end namespace
