#ifndef MOUSE_H
#define MOUSE_H

#include "Component.h" // Base class: boxModel::core::Component
#include "Box.h"
#include "Stack.h"

namespace boxModel {

namespace components {

class Mouse : public boxModel::core::Component {
public:
	Mouse();
	~Mouse();
	
	void setup();
	
	core::Point mousePos;
	core::Point mousePosOld;
	bool isMouseOver;
	
	virtual void onMouseMove(float mouseX, float mouseY){};
	//virtual void onMouseMoveOutside(float mouseX, float mouseY){};
	virtual void onMousePress(float mouseX, float mouseY, int button){};
	virtual void onMouseRelease(float mouseX, float mouseY, int button){};
	virtual void onMouseDrag(float mouseX, float mouseY, int button){};
	virtual void onMouseReleaseOutside(float mouseX, float mouseY, int button){};
	virtual void onMouseEnter(float mouseX, float mouseY){};
	virtual void onMouseExit(float mouseX, float mouseY){};
	
	Nano::signal<void(float mouseX, float mouseY)> mouseMove;
	Nano::signal<void(float mouseX, float mouseY, int button)> mousePress;
	Nano::signal<void(float mouseX, float mouseY, int button)> mouseRelease;
	Nano::signal<void(float mouseX, float mouseY, int button)> mouseDrag;
	Nano::signal<void(float mouseX, float mouseY, int button)> mouseClick;
	Nano::signal<void(float mouseX, float mouseY, int button)> mouseReleaseOutside;	
	Nano::signal<void(float mouseX, float mouseY)> mouseEnter;
	Nano::signal<void(float mouseX, float mouseY)> mouseExit;
	
	Nano::signal<void(float mouseX, float mouseY, Mouse* m)> mouseMoveRef;
	Nano::signal<void(float mouseX, float mouseY, int button, Mouse* m)> mousePressRef;
	Nano::signal<void(float mouseX, float mouseY, int button, Mouse* m)> mouseReleaseRef;
	Nano::signal<void(float mouseX, float mouseY, int button, Mouse* m)> mouseDragRef;
	Nano::signal<void(float mouseX, float mouseY, int button, Mouse* m)> mouseReleaseOutsideRef;
	Nano::signal<void(float mouseX, float mouseY, int button, Mouse* m)> mouseClickRef;	
	Nano::signal<void(float mouseX, float mouseY, Mouse* m)> mouseEnterRef;
	Nano::signal<void(float mouseX, float mouseY, Mouse* m)> mouseExitRef;
	
	void setMousePos(float x, float y);
	void setMouseButtonPressed(int button);
	void setMouseButtonReleased(int button);
	
private:
	void onStack(Stack* stack);
	void onBox(Box* box);
	
	Stack* stack;
	Box* box;
	
	std::map<int, bool> buttonStates;
	
	bool capture;
	
	long int lastClick;
};

}

}

#endif // MOUSE_H
