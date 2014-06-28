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
	LISTEN_FOR_COMPONENT(Serializer, ButtonComponent, onSerializer)
}

void ButtonComponent::onMouse(Mouse* m) {
	mouse = m;
	mouse->enableMouse();
	mouse->mouseClick.connect<ButtonComponent, &ButtonComponent::onClick>(this);
}

void ButtonComponent::onAddressable(Addressable* a) {
	addressable = a;
}

void ButtonComponent::onSerializer(components::Serializer* serializer) {
	serializer->deserialized.connect<ButtonComponent, &ButtonComponent::onDeserialize>(this);
}

std::string ButtonComponent::getName() {
	return "ButtonComponent";
}

void ButtonComponent::setButtonType(ButtonType type) {
	buttonType = type;
}

void ButtonComponent::onClick(float mouseX, float mouseY, int button) {
	if(buttonType == TOGGLE) {
		value.set(!value.get());
		if(addressable) {
			if(value.get())
				addressable->addClass("active");
			else
				addressable->removeClass("active");
		}
	} else if(buttonType == BANG) {
		value.set(true);
		value.set(false);
	}
}

void ButtonComponent::onDeserialize(boxModel::core::VariantList& variants) {
	if(variants.hasKey("type")) {
		string type = variants.get("type");
		if(type == "bang") {
			setButtonType(BANG);
		} else if(type == "toggle") {
			setButtonType(TOGGLE);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

Button::Button() {
	addComponent<boxModel::gui::ButtonComponent>(this);
	addComponent<boxModel::components::Image>(this);
	
	value.changed.connect<Button, &Button::valueChanged>(this);
}

std::string Button::getType() {
	return "button";
}

void Button::valueChanged(bool val) {
	changed(this);
}

}
}
