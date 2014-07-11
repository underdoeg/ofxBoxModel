#ifndef MOUSE_H
#define MOUSE_H

#include "Component.h" // Base class: boxModel::core::Component
#include "BoxDefinition.h"
#include "Stack.h"
#include "components/Css.h"
#include "components/Style.h"


namespace boxModel {

namespace components {

class Mouse : public boxModel::core::Component {
public:
	class ButtonStates {
	public:
		bool isPressed(int button);
		bool isAnyPressed();
		unsigned long getTime(int button);
	private:
		void setPressed(int button);
		void setReleased(int button);
		void updateTime(int button);
		std::map<int, bool> states;
		std::map<int, unsigned long long> time;
		friend class Mouse;
	};

	Mouse();
	~Mouse();

	std::string getName();

	void setup();

	core::Point mousePos;
	core::Point mousePosInside;
	core::Point mousePosOld;

	virtual void onMouseMove(float mouseX, float mouseY) {};
	virtual void onMouseMoveOutside(float mouseX, float mouseY) {};
	virtual void onMousePress(float mouseX, float mouseY, int button) {};
	virtual void onMouseRelease(float mouseX, float mouseY, int button) {};
	virtual void onMouseDrag(float mouseX, float mouseY, ButtonStates& buttons) {};
	virtual void onMouseDragOutside(float mouseX, float mouseY, ButtonStates& buttons) {};
	virtual void onMouseReleaseOutside(float x, float y, int button) {};
	virtual void onMouseClick(float mouseX, float mouseY, int button) {};
	virtual void onMouseDoubleClick(float mouseX, float mouseY, int button) {}; //TODO: implement double click
	virtual void onMouseEnter(float mouseX, float mouseY) {};
	virtual void onMouseExit() {};

	Nano::Signal<void(float mouseX, float mouseY)> mouseMove;
	Nano::Signal<void(float mouseX, float mouseY)> mouseMoveOutside;
	Nano::Signal<void(float mouseX, float mouseY, int button)> mousePress;
	Nano::Signal<void(float mouseX, float mouseY, int button)> mouseRelease;
	Nano::Signal<void(float mouseX, float mouseY, ButtonStates& buttons)> mouseDrag;
	Nano::Signal<void(float mouseX, float mouseY, ButtonStates& buttons)> mouseDragOutside;
	Nano::Signal<void(float mouseX, float mouseY, int button)> mouseReleaseOutside;
	Nano::Signal<void(float mouseX, float mouseY, int button)> mouseClick;
	Nano::Signal<void(float mouseX, float mouseY, int button)> mouseDoubleClick;
	Nano::Signal<void(float mouseX, float mouseY)> mouseEnter;
	Nano::Signal<void()> mouseExit;

	Nano::Signal<void(float mouseX, float mouseY, Mouse* m)> mouseMoveRef;
	Nano::Signal<void(float mouseX, float mouseY, Mouse* m)> mouseMoveOutsideRef;
	Nano::Signal<void(float mouseX, float mouseY, int button, Mouse* m)> mousePressRef;
	Nano::Signal<void(float mouseX, float mouseY, int button, Mouse* m)> mouseReleaseRef;
	Nano::Signal<void(float mouseX, float mouseY, ButtonStates& buttons, Mouse* m)> mouseDragRef;
	Nano::Signal<void(float mouseX, float mouseY, ButtonStates& buttons, Mouse* m)> mouseDragOutsideRef;
	Nano::Signal<void(float mouseX, float mouseY, int button, Mouse* m)> mouseReleaseOutsideRef;
	Nano::Signal<void(float mouseX, float mouseY, int button, Mouse* m)> mouseClickRef;
	Nano::Signal<void(float mouseX, float mouseY, int button, Mouse* m)> mouseDoubleClickRef;
	Nano::Signal<void(float mouseX, float mouseY, Mouse* m)> mouseEnterRef;
	Nano::Signal<void(Mouse* m)> mouseExitRef;

	void setMousePos(float x, float y);
	void setMouseButtonPressed(int button);
	void setMouseButtonReleased(int button);

	void routeMouse(Mouse* mouse, bool blocking=false);
	void removeRouteMouse();

	void setMouseIgnore(bool state);
	void enableMouse();

	bool isMouseButtonPressed(int button);
	bool isMouseOver();

	static unsigned long clickTime;
	static unsigned long doubleClickTime;

	void getInfo(core::Component::Info& info);

private:

	bool bMouseOver;

	void onStack(Stack* stack);
	void onBox(BoxDefinition* box);
	void onCss(Css* css);
	void onStyle(Style* style);

	bool handleMouseMove(float x, float y);
	void handleMouseExit(float x, float y);
	bool handleMousePressed(int button);
	bool handleMouseReleased(int button);
	void handleMouseReleasedOutside(int button);

	void pMouse(std::string key, std::string value);

	Stack* stack;
	BoxDefinition* box;
	Style* style;

	ButtonStates buttonStates;

	bool passEventsThrough;

	Mouse* route;
	bool bCaptureBlock;

};

}

}

#endif // MOUSE_H
