#include "Mouse.h"
#include "time.h"

namespace boxModel {

namespace components {

Mouse::Mouse() {
}

Mouse::~Mouse() {
}

void Mouse::setup() {
	isMouseOver = false;
	stack = NULL;
	box = NULL;
	LISTEN_FOR_COMPONENT(Stack, Mouse, onStack)
	LISTEN_FOR_COMPONENT(Box, Mouse, onBox)

	mouseMove.connect<Mouse, &Mouse::onMouseMove>(this);
	mousePress.connect<Mouse, &Mouse::onMousePress>(this);
	mouseRelease.connect<Mouse, &Mouse::onMouseRelease>(this);
	mouseDrag.connect<Mouse, &Mouse::onMouseDrag>(this);
	mouseReleaseOutside.connect<Mouse, &Mouse::onMouseReleaseOutside>(this);
	mouseEnter.connect<Mouse, &Mouse::onMouseEnter>(this);
	mouseExit.connect<Mouse, &Mouse::onMouseExit>(this);
}

void Mouse::onStack(Stack* s) {
	stack = s;
}

void Mouse::onBox(Box* b) {
	box = b;
}

void Mouse::setMouseButtonPressed(int button) {
	if(isMouseOver)
		buttonStates[button] = true;
}

void Mouse::setMouseButtonReleased(int button) {
	if(isMouseOver)
		buttonStates[button] = false;
}

void Mouse::setMousePos(float x, float y) {
	if(box != 0) {
		if(!box->isInsideContent(x, y)) { //TODO: report mouse outside as well?
			if(isMouseOver) {
				mouseExit(x, y);
				mouseExitRef(x, y, this);
			}
			isMouseOver = false;
			return;
		}
		if(!isMouseOver) {
			mouseEnter(x, y);
			mouseEnterRef(x, y, this);
		}
		isMouseOver = true;
		x -= box->position.x + box->contentPosition.x;
		y -= box->position.y + box->contentPosition.y;
	}

	mousePos.x = x;
	mousePos.y = y;

	mouseMove(x, y);
	mouseMoveRef(x, y, this);

	if(stack != NULL) {
		for(unsigned int i=0; i<stack->getNumChildren(); i++) {
			Stack * child = stack->getChild(i);
			if(child->components->hasComponent<Mouse>()) {
				child->components->getComponent<Mouse>()->setMousePos(mousePos.x, mousePos.y);
			}
		}
	}
}

}

}
