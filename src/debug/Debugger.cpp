#include "Debugger.h"
#include "components/Mouse.h"
#include "components/Draw.h"

namespace boxModel {

namespace debug {

Debugger::Debugger() {
	curInfoViewer = NULL;
	addComponent<components::Draggable>(this);
	title.text = "DEBUGGER";
	addChild(&title);
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

	if(rootContainer->hasComponent<components::Stack>()) {
		components::Stack* stack = rootContainer->getComponent<Stack>();

		if(stack->components->hasComponent<components::Draw>()) {
			stack->components->getComponent<components::Draw>()->postDraw.connect<Draw, &Draw::draw>(this);
		}


		/*
		components::Stack::ChildrenList children = stack->getChildrenRecursive();
		children.push_back(stack);
		for(Stack* child: children) {
			if(child->components->hasComponent<components::Mouse>()) {
				components::Mouse* mouse = child->components->getComponent<Mouse>();
				//listen for mosue clicks
				mouse->mouseClickRef.connect<Debugger, &Debugger::onClick>(this);
			}
		}
		*/
	}

	//route mouse events
	if(rootContainer->hasComponent<components::Mouse>()) {
		components::Mouse* m = rootContainer->getComponent<components::Mouse>();
		m->routeMouse(this, true);
	}
}

void Debugger::onMouseReleaseOutside(float mouseX, float mouseY, int button) {
	if(curInfoViewer != NULL)
		curInfoViewer->hide();

	if(rootContainer->hasComponent<Stack>()) {
		boxModel::components::Stack* childStack = rootContainer->getComponent<Stack>();
		core::ComponentContainer* container = childStack->containerAt(mouseX, mouseY);
		if(container == NULL)
			return;

		if(infoViewers.find(container) == infoViewers.end())
			addChild(&infoViewers[container]);
		InfoViewer& iv = infoViewers[container];
		iv.setComponentContainer(container);
		curInfoViewer = &iv;
		infoViewers[container].show();
		flush();
	}
}

void Debugger::onMouseMove(float mouseX, float mouseY) {

}

void Debugger::onMouseMoveOutside(float mouseX, float mouseY) {
}


}
} // end namespace
