#include "Debugger.h"
#include "components/Mouse.h"
#include "components/Draw.h"

namespace boxModel {

namespace debug {

Debugger::Debugger() {
	curInfoViewer = NULL;
	addComponent<components::Draggable>(this);
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
	if(rootContainer->hasComponent<components::Stack>()) {
		components::Stack* stack = rootContainer->getComponent<Stack>();

		if(stack->components->hasComponent<components::Draw>()) {
			stack->components->getComponent<components::Draw>()->postDraw.connect<Draw, &Draw::draw>(this);
		}

		components::Stack::ChildrenList children = stack->getChildrenRecursive();
		children.push_back(stack);
		for(Stack* child: children) {
			if(child->components->hasComponent<components::Mouse>()) {
				components::Mouse* mouse = child->components->getComponent<Mouse>();
				//listen for mosue clicks
				mouse->mouseClickRef.connect<Debugger, &Debugger::onComponentClick>(this);
			}
		}
	}
}

void Debugger::onComponentClick(int button, components::Mouse* mouse) {
	if(curInfoViewer != NULL)
		curInfoViewer->hide();

	core::ComponentContainer* container = mouse->components;
	if(infoViewers.find(container) == infoViewers.end())
		addChild(&infoViewers[container]);
	InfoViewer& iv = infoViewers[container];
	iv.setComponentContainer(container);
	curInfoViewer = &iv;
	infoViewers[container].show();
	flush();
}

}
} // end namespace
