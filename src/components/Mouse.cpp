#include "Mouse.h"
#include "core/Utils.h"

namespace boxModel {

namespace components {

/////////////////////////////////////////////////////////////////////////////////////////////

bool Mouse::ButtonStates::isPressed(int button) {
	return states[button];
}

bool Mouse::ButtonStates::isAnyPressed() {
	for(auto state: states) {
		if(state.second == true)
			return true;
	}
	return false;
}

void Mouse::ButtonStates::setPressed(int button) {
	states[button] = true;
	updateTime(button);
}

void Mouse::ButtonStates::setReleased(int button) {
	states[button] = false;
	updateTime(button);
}

void Mouse::ButtonStates::updateTime(int button) {
	time[button] = core::getSystemTime();
}

unsigned long Mouse::ButtonStates::getTime(int button) {
	if(time[button] == 0)
		updateTime(button);
	return core::getSystemTime() - time[button];
}

/////////////////////////////////////////////////////////////////////////////////////////////

unsigned long Mouse::clickTime = 500;
unsigned long Mouse::doubleClickTime = 400;

Mouse::Mouse() {
}

Mouse::~Mouse() {
}

std::string Mouse::getName() {
	return "mouse";
}

void Mouse::setup() {
	route = NULL;
	passEventsThrough = false;
	bMouseOver = false;
	stack = NULL;
	style = NULL;
	box = NULL;
	LISTEN_FOR_COMPONENT(Stack, Mouse, onStack)
	LISTEN_FOR_COMPONENT(BoxDefinition, Mouse, onBox)
	LISTEN_FOR_COMPONENT(Css, Mouse, onCss)
	LISTEN_FOR_COMPONENT(Style, Mouse, onStyle)
	
	/*
	mouseMove.connect<Mouse, &Mouse::onMouseMove>(this);
	mouseMoveOutside.connect<Mouse, &Mouse::onMouseMoveOutside>(this);
	mousePress.connect<Mouse, &Mouse::onMousePress>(this);
	mouseRelease.connect<Mouse, &Mouse::onMouseRelease>(this);
	mouseClick.connect<Mouse, &Mouse::onMouseClick>(this);
	mouseDoubleClick.connect<Mouse, &Mouse::onMouseDoubleClick>(this);
	mouseDrag.connect<Mouse, &Mouse::onMouseDrag>(this);
	mouseReleaseOutside.connect<Mouse, &Mouse::onMouseReleaseOutside>(this);
	mouseEnter.connect<Mouse, &Mouse::onMouseEnter>(this);
	mouseExit.connect<Mouse, &Mouse::onMouseExit>(this);
	*/
}

void Mouse::onStack(Stack* s) {
	stack = s;
}

void Mouse::onStyle(Style* s) {
	style = s;
}

void Mouse::onBox(BoxDefinition* b) {
	box = b;
}

void Mouse::onCss(Css* css) {
	css->addCssParserFunction<Mouse, &Mouse::pMouse>("mouse", this);
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

void Mouse::setMouseIgnore(bool state) {
	passEventsThrough = state;
}

// handle mosue movement, return true if it was handled
bool Mouse::handleMouseMove(float x, float y) {
	
	if(style){
		if(!style->isVisible())
			return false;
	}
	
	if(route != NULL) {
		route->handleMouseMove(x, y);
		if(bCaptureBlock)
			return true;
	}

	bool ret = false;

	float xInside = x - box->position.x - box->contentPosition.x;
	float yInside = y - box->position.y - box->contentPosition.y;
	
	mousePosOld = mousePos;
	mousePos.x = xInside;
	mousePos.y = yInside;

	bool handledByChild = false;

	if(stack != NULL) {

		//loop children in reverse because children with a higher index should handle the mouse first
		for(int i= stack->getNumChildren() - 1; i>=0; i--) {
			Stack * child = stack->getChild(i);

			if(child->components->hasComponent<BoxDefinition>()) {
				//check if child even has a mouse component
				if(child->components->hasComponent<Mouse>()) {
					//check if child handles the mouse
					if(!handledByChild) {
						if(child->components->getComponent<Mouse>()->handleMouseMove(xInside, yInside)) {
							handledByChild = true;
							ret = true;
						}
					} else {
						child->components->getComponent<Mouse>()->handleMouseExit(xInside, yInside);
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
			onMouseEnter(xInside, yInside);
		}

		mousePosInside = mousePos;

		if(buttonStates.isAnyPressed()) {
			mouseDrag(xInside, yInside, buttonStates);
			mouseDragRef(xInside, yInside, buttonStates, this);
			onMouseDrag(xInside, yInside, buttonStates);
		} else {
			mouseMove(xInside, yInside);
			mouseMoveRef(xInside, yInside, this);
			onMouseMove(xInside, yInside);
		}
		ret = true;
	} else {
		handleMouseExit(x, y);
	}

	if(passEventsThrough && !handledByChild)
		return false;

	return ret;
}
void Mouse::handleMouseExit(float x, float y) {
	if(isMouseOver()) {
		bMouseOver = false;
		mouseExit();
		mouseExitRef(this);
	}
	float xInside = x - box->position.x - box->contentPosition.x;
	float yInside = y - box->position.y - box->contentPosition.y;
	
	mousePosOld = mousePos;
	mousePos.x = xInside;
	mousePos.y = yInside;
	
	if(buttonStates.isAnyPressed()) {
		mouseDragOutside(xInside, yInside, buttonStates);
		mouseDragOutsideRef(xInside, yInside, buttonStates, this);
		onMouseDragOutside(xInside, yInside, buttonStates);
	} else {
		mouseMoveOutside(xInside, yInside);
		mouseMoveOutsideRef(xInside, yInside, this);
		onMouseMoveOutside(xInside, yInside);
	}
}

bool Mouse::handleMousePressed(int button) {
	if(style){
		if(!style->isVisible())
			return false;
	}
	
	if(route != NULL) {
		route->handleMousePressed(button);
		if(bCaptureBlock)
			return true;
	}

	bool ret = false;
	bool handledByChild = false;
	if(stack != NULL) {

		//loop children in reverse because children with a higher index should handle the mouse first
		for(int i= stack->getNumChildren() - 1; i>=0; i--) {
			Stack * child = stack->getChild(i);

			if(child->components->hasComponent<BoxDefinition>()) {
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
			onMousePress(mousePos.x, mousePos.y, button);
		}
		ret = true;
	}

	if(passEventsThrough && !handledByChild)
		return false;

	return ret;
}

bool Mouse::handleMouseReleased(int button) {
	if(style){
		if(!style->isVisible()){
			return false;
		}
	}
	
	if(route != NULL) {
		route->handleMouseReleased(button);
		if(bCaptureBlock)
			return true;
	}

	bool ret = false;
	bool handledByChild = false;
	if(stack != NULL) {

		//loop children in reverse because children with a higher index should handle the mouse first
		for(int i= stack->getNumChildren() - 1; i>=0; i--) {
			Stack * child = stack->getChild(i);

			if(child->components->hasComponent<BoxDefinition>()) {
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
			onMouseRelease(mousePos.x, mousePos.y, button);
			
			//check if it is a click
			if(timeAgo < clickTime) {
				mouseClick(mousePos.x, mousePos.y, button);
				mouseClickRef(mousePos.x, mousePos.y, button, this);
				onMouseClick(mousePos.x, mousePos.y, button);
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
		mouseReleaseOutside(mousePos.x, mousePos.y, button);
		mouseReleaseOutsideRef(mousePos.x, mousePos.y, button, this);
		onMouseReleaseOutside(mousePos.x, mousePos.y, button);
	}
}

bool Mouse::isMouseButtonPressed(int button) {
	return buttonStates.isPressed(button);
}

bool Mouse::isMouseOver() {
	return bMouseOver;
}

void Mouse::routeMouse(Mouse* mouse, bool blocking) {
	route = mouse;
	bCaptureBlock = blocking;
}

void Mouse::removeRouteMouse()
{
	route = NULL;
	bCaptureBlock = false;
}

void Mouse::pMouse(std::string key, std::string value) {
	if(value == "ignore") {
		setMouseIgnore(true);
	}
}

void Mouse::getInfo(core::Component::Info& info) {

}

} // end namespace

}
