#include "BoxDefinition.h"
#include "Stack.h"
#include "core/Utils.h"

using namespace boxModel::core;
using namespace boxModel::components;

std::string BoxDefinition::getName() {
	return "box";
}

void BoxDefinition::setup() {
	stack = NULL;

	contentSize.changed.connect<BoxDefinition, &BoxDefinition::onContentSizeChanged>(this);
	position.changed.connect<BoxDefinition, &BoxDefinition::onPositionChanged>(this);

	LISTEN_FOR_COMPONENT(Stack, BoxDefinition, onStack)
}

void BoxDefinition::onStack(Stack* s) {
	stack = s;
	onContentSizeChanged(contentSize);
	stack->childAdded.connect<BoxDefinition, &BoxDefinition::onChildAdded>(this);
}

Point BoxDefinition::getGlobalPosition() {
	if(!components->hasComponent<Stack>())
		return position;
	Point pos;
	Stack* rootStack = components->getComponent<Stack>();
	Stack* stack = rootStack;
	int i = 0;
	while(stack->hasParent()) {
		if(stack->components->hasComponent<BoxDefinition>()) {
			BoxDefinition* box = stack->components->getComponent<BoxDefinition>();
			pos += box->position;//box->contentPosition;
			if(stack != rootStack)
				pos += box->contentPosition;// << endl;
		}
		stack = stack->getParent();
		i++;
	}
	if(stack != rootStack && stack->components->hasComponent<BoxDefinition>()) {
		BoxDefinition* box = stack->components->getComponent<BoxDefinition>();
		pos += box->contentPosition;
	}
	return pos;
}

void BoxDefinition::onContentSizeChanged(core::Point p) {
	if(stack != NULL) {
		for(Stack* child: stack->getChildren()) {
			child->components->setUnitContainerSize(p.x, p.y);
		}
	}
}

void BoxDefinition::onPositionChanged(core::Point p) {
	notifyChildrenPositionChanged();
}

void BoxDefinition::notifyChildrenPositionChanged() {
	globalPositionChanged();
	if(stack != NULL) {
		for(Stack* child: stack->getChildren()) {
			if(child->components->hasComponent<BoxDefinition>())
				child->components->getComponent<BoxDefinition>()->notifyChildrenPositionChanged();
		}
	}
}

void BoxDefinition::onChildAdded(Stack* child) {
	child->components->setUnitContainerSize(contentSize.x, contentSize.y);
}

void BoxDefinition::copyFrom(BoxDefinition* box) {
	position = box->position;
	outerSize = box->outerSize;
	size = box->size;
	contentSize = box->contentSize;
	contentPosition = box->contentPosition;
}

////

bool BoxDefinition::isInside(core::Point p) {
	return isInside(p.x, p.y);
}

bool BoxDefinition::isInside(float x, float y) {
	return core::rectContains(x, y, position.x, position.y, size.x, size.y);
}

bool BoxDefinition::isInsideContent(core::Point p) {
	return isInsideContent(p.x, p.y);
}
bool BoxDefinition::isInsideContent(float x, float y) {
	return core::rectContains(x, y, position.x + contentPosition.x, position.y + contentPosition.y, contentSize.x, contentSize.y);
}

void BoxDefinition::getInfo(core::Component::Info& info) {
	info["position"] = "0,0";
}
