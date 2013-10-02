#include "Mouse.h"
#include "core/Utils.h"

namespace boxModel {

namespace components {

/////////////////////////////////////////////////////////////////////////////////////////////

bool Mouse::ButtonStates::isPressed(int button)
{
	return states[button];
}

bool Mouse::ButtonStates::isAnyPressed()
{
	for(auto state: states) {
		if(state.second == true)
			return true;
	}
	return false;
}

void Mouse::ButtonStates::setPressed(int button)
{
	states[button] = true;
	updateTime(button);
}

void Mouse::ButtonStates::setReleased(int button)
{
	states[button] = false;
	updateTime(button);
}

void Mouse::ButtonStates::updateTime(int button)
{
	time[button] = core::getSystemTime();
}

unsigned long Mouse::ButtonStates::getTime(int button)
{
	if(time[button] == 0)
		updateTime(button);
	return core::getSystemTime() - time[button];
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned long Mouse::clickTime = 400;
unsigned long Mouse::doubleClickTime = 400;

Mouse::Mouse() {
}

Mouse::~Mouse() {
}

void Mouse::setup() {
	passEventsThrough = false;
	bMouseOver = false;
	stack = NULL;
	box = NULL;
	LISTEN_FOR_COMPONENT(Stack, Mouse, onStack)
	LISTEN_FOR_COMPONENT(Box, Mouse, onBox)

	mouseMove.connect<Mouse, &Mouse::onMouseMove>(this);
	mousePress.connect<Mouse, &Mouse::onMousePress>(this);
	mouseRelease.connect<Mouse, &Mouse::onMouseRelease>(this);
	mouseClick.connect<Mouse, &Mouse::onMouseClick>(this);
	mouseDoubleClick.connect<Mouse, &Mouse::onMouseDoubleClick>(this);
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
	handleMousePressed(button);
}

void Mouse::setMouseButtonReleased(int button) {
	handleMouseReleased(button);
}

void Mouse::setMousePos(float x, float y) {
	handleMouseMove(x, y);
}

// handle mosue movement, return true if it was handled
bool Mouse::handleMouseMove(float x, float y) {

	bool ret = false;

	float xInside = x - box->position.x - box->contentPosition.x;
	float yInside = y - box->position.y - box->contentPosition.y;

	bool handledByChild = false;

	if(stack != NULL) {

		//loop children in reverse because children with a higher index should handle the mouse first
		for(int i= stack->getNumChildren() - 1; i>=0; i--) {
			Stack * child = stack->getChild(i);

			if(child->components->hasComponent<Box>()) {
				//check if child even has a mouse component
				if(child->components->hasComponent<Mouse>()) {
					//check if child handles the mouse
					if(!handledByChild) {
						if(child->components->getComponent<Mouse>()->handleMouseMove(xInside, yInside)) {
							handledByChild = true;
							ret = true;
						}
					} else {
						child->components->getComponent<Mouse>()->handleMouseExit();
					}
				}
			}
		}
	}

	bool mouseInside = true;

	if(box != NULL) {
		mouseInside = box->isInside(x, y);
	}

	if(!handledByChild && mouseInside) {
		if(!isMouseOver()) {
			bMouseOver = true;
			mouseEnter(xInside, yInside);
			mouseEnterRef(xInside, yInside, this);
		}
		mousePos.x = xInside;
		mousePos.y = yInside;
		
		if(buttonStates.isAnyPressed()){
			mouseDrag(xInside, yInside, buttonStates);
			mouseDragRef(xInside, yInside, buttonStates, this);
		}else{
			mouseMove(xInside, yInside);
			mouseMoveRef(xInside, yInside, this);
		}
		ret = true;
	} else {
		handleMouseExit();
	}

	if(passEventsThrough && !handledByChild)
		return false;

	return ret;
}

void Mouse::handleMouseExit() {
	if(isMouseOver()) {
		bMouseOver = false;
		mouseExit();
		mouseExitRef(this);
	}
}

bool Mouse::handleMousePressed(int button) {
	bool ret = false;
	bool handledByChild = false;
	if(stack != NULL) {

		//loop children in reverse because children with a higher index should handle the mouse first
		for(int i= stack->getNumChildren() - 1; i>=0; i--) {
			Stack * child = stack->getChild(i);

			if(child->components->hasComponent<Box>()) {
				//check if child even has a mouse component
				if(child->components->hasComponent<Mouse>()) {
					//check if child handles the mouse
					if(!handledByChild) {
						if(child->components->getComponent<Mouse>()->handleMousePressed(button)) {
							handledByChild = true;
							ret = true;
						}
					}
				}
			}
		}
	}

	if(isMouseOver() && !handledByChild) {
		if(!buttonStates.isPressed(button)) {
			buttonStates.setPressed(button);
			mousePress(mousePos.x, mousePos.y, button);
			mousePressRef(mousePos.x, mousePos.y, button, this);
		}
		ret = true;
	}

	if(passEventsThrough && !handledByChild)
		return false;

	return ret;
}

bool Mouse::handleMouseReleased(int button) {
	bool ret = false;
	bool handledByChild = false;
	if(stack != NULL) {

		//loop children in reverse because children with a higher index should handle the mouse first
		for(int i= stack->getNumChildren() - 1; i>=0; i--) {
			Stack * child = stack->getChild(i);

			if(child->components->hasComponent<Box>()) {
				//check if child even has a mouse component
				if(child->components->hasComponent<Mouse>()) {
					//check if child handles the mouse
					if(!handledByChild) {
						if(child->components->getComponent<Mouse>()->handleMouseReleased(button)) {
							handledByChild = true;
							ret = true;
						}
					} else {
						child->components->getComponent<Mouse>()->handleMouseReleasedOutside(button);
					}
				}
			}
		}
	}

	if(isMouseOver() && !handledByChild) {
		if(buttonStates.isPressed(button)) {
			unsigned long timeAgo = buttonStates.getTime(button);
			buttonStates.setReleased(button);
			mouseRelease(mousePos.x, mousePos.y, button);
			mouseReleaseRef(mousePos.x, mousePos.y, button, this);
			
			//check if it is a click
			if(timeAgo < clickTime){
				mouseClick(button);
				mouseClickRef(button, this);
			}
		}
		ret = true;
	} else {
		handleMouseReleasedOutside(button);
	}
	
	if(passEventsThrough && !handledByChild)
		return false;

	return ret;
}
void Mouse::handleMouseReleasedOutside(int button) {
	if(buttonStates.isPressed(button)) {
		buttonStates.setReleased(button);
		mouseReleaseOutside(button);
		mouseReleaseOutsideRef(button, this);
	}
}

bool Mouse::isMouseButtonPressed(int button)
{
	return buttonStates.isPressed(button);
}

bool Mouse::isMouseOver()
{
	return bMouseOver;
}

} // end namespace

}

