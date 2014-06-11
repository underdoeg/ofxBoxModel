#ifndef BUTTON_H
#define BUTTON_H

#include "Box.h"

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
	
	std::string getName();
	
	void setup();
	
	core::Value<bool> value;
	
private:
	void onMouse(components::Mouse* mouse);
	void onAddressable(components::Addressable* addressable);
	
	void onClick(float mouseX, float mouseY, int button);

	components::Mouse* mouse;
	components::Addressable* addressable;
	ButtonType buttonType;
};

class Button: public boxes::Box, ButtonComponent {
public:
	Button();
	
	virtual std::string getType();

private:

};

}
}

#endif // BUTTON_H
