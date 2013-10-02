#ifndef MOUSE_H
#define MOUSE_H

#include "Component.h" // Base class: boxModel::core::Component
#include "Box.h"
#include "Stack.h"

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

	void setup();

	core::Point mousePos;
	core::Point mousePosOld;

	virtual void onMouseMove(float mouseX, float mouseY) {};
	virtual void onMouseMoveOutside(float mouseX, float mouseY) {};
	virtual void onMousePress(float mouseX, float mouseY, int button) {};
	virtual void onMouseRelease(float mouseX, float mouseY, int button) {};
	virtual void onMouseDrag(float mouseX, float mouseY, ButtonStates& buttons) {};
	virtual void onMouseReleaseOutside(int button) {};
	virtual void onMouseClick(int button) {};
	virtual void onMouseDoubleClick(int button) {}; //TODO: implement double click
	virtual void onMouseEnter(float mouseX, float mouseY) {};
	virtual void onMouseExit() {};

	Nano::signal<void(float mouseX, float mouseY)> mouseMove;
	Nano::signal<void(float mouseX, float mouseY, int button)> mousePress;
	Nano::signal<void(float mouseX, float mouseY, int button)> mouseRelease;
	Nano::signal<void(float mouseX, float mouseY, ButtonStates& buttons)> mouseDrag;
	Nano::signal<void(int button)> mouseReleaseOutside;
	Nano::signal<void(int button)> mouseClick;
	Nano::signal<void(int button)> mouseDoubleClick;
	Nano::signal<void(float mouseX, float mouseY)> mouseEnter;
	Nano::signal<void()> mouseExit;

	Nano::signal<void(float mouseX, float mouseY, Mouse* m)> mouseMoveRef;
	Nano::signal<void(float mouseX, float mouseY, int button, Mouse* m)> mousePressRef;
	Nano::signal<void(float mouseX, float mouseY, int button, Mouse* m)> mouseReleaseRef;
	Nano::signal<void(float mouseX, float mouseY, ButtonStates& buttons, Mouse* m)> mouseDragRef;
	Nano::signal<void(int button, Mouse* m)> mouseReleaseOutsideRef;
	Nano::signal<void(int button, Mouse* m)> mouseClickRef;
	Nano::signal<void(int button, Mouse* m)> mouseDoubleClickRef;
	Nano::signal<void(float mouseX, float mouseY, Mouse* m)> mouseEnterRef;
	Nano::signal<void(Mouse* m)> mouseExitRef;

	void setMousePos(float x, float y);
	void setMouseButtonPressed(int button);
	void setMouseButtonReleased(int button);

	bool isMouseButtonPressed(int button);
	bool isMouseOver();

	static unsigned long clickTime;
	static unsigned long doubleClickTime;

private:

	bool bMouseOver;

	void onStack(Stack* stack);
	void onBox(Box* box);

	bool handleMouseMove(float x, float y);
	void handleMouseExit();
	bool handleMousePressed(int button);
	bool handleMouseReleased(int button);
	void handleMouseReleasedOutside(int button);

	Stack* stack;
	Box* box;

	ButtonStates buttonStates;

	bool passEventsThrough;

};

}

}

#endif // MOUSE_H
