#include "Button.h"

namespace boxModel {

using namespace components;

namespace gui {


ButtonComponent::ButtonComponent() {
	mouse = NULL;
	addressable = NULL;
	buttonType = TOGGLE;
	value.set(false);
}

ButtonComponent::~ButtonComponent() {
}

void ButtonComponent::setup() {
	LISTEN_FOR_COMPONENT(Addressable, ButtonComponent, onAddressable)
	LISTEN_FOR_COMPONENT(Mouse, ButtonComponent, onMouse)
}

void ButtonComponent::onMouse(Mouse* m) {
	mouse = m;
	mouse->mouseClick.connect<ButtonComponent, &ButtonComponent::onClick>(this);
}

void ButtonComponent::onAddressable(Addressable* a) {
	addressable = a;
}	

std::string ButtonComponent::getName() {
	return "ButtonComponent";
}

void ButtonComponent::onClick(float mouseX, float mouseY, int button){
	if(buttonType == TOGGLE){
		value.set(!value.get());
		if(addressable){
			if(value.get())
				addressable->addClass("active");
			else
				addressable->removeClass("active");
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

Button::Button() {
	addComponent<boxModel::gui::ButtonComponent>(this);
}

std::string Button::getType() {
	return "button";
}



}
}
