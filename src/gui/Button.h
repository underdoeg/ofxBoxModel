#ifndef BUTTON_H
#define BUTTON_H

#include "Box.h"
#include "Texts.h"

namespace boxModel {

namespace gui {

enum ButtonType{
	BANG,
	TOGGLE
};
	
class ButtonComponent: public core::Component {
public:
	ButtonComponent();
	~ButtonComponent();
	
	void setup();
	std::string getName();
	void setButtonType(ButtonType type);

	core::Value<bool> value;	
	
private:
	void onMouse(components::Mouse* mouse);
	void onAddressable(components::Addressable* addressable);
	void onSerializer(components::Serializer* serializer);
	
	void onDeserialize(boxModel::core::VariantList& variants);
	
	void onClick(float mouseX, float mouseY, int button);

	components::Mouse* mouse;
	components::Addressable* addressable;
	components::Serializer* serializer;
	ButtonType buttonType;
};

class Button: public boxes::TextBox, public ButtonComponent {
public:
	Button();
	
	virtual std::string getType();
	
	Nano::signal<void(Button*)> changed;
	
private:
	void valueChanged(bool val);
};

}
}

#endif // BUTTON_H
