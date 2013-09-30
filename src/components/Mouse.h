#ifndef MOUSE_H
#define MOUSE_H

#include "Component.h" // Base class: boxModel::core::Component

namespace boxModel {

namespace components {

class Mouse : public boxModel::core::Component {
public:
	Mouse();
	~Mouse();
	
	core::Point mousePos;
	core::Point mousePosOld;
	
	virtual void onMouseMove(int mouseX, int mouseY){};
	virtual void onMousePress(int mouseX, int mouseY, int button){};
	virtual void onMouseRelease(int mouseX, int mouseY, int button){};
	virtual void onMouseDrag(int mouseX, int mouseY, int button){};
	virtual void onMouseReleaseOutside(int mouseX, int mouseY, int button){};
	
	void setup();
	
	void setMousePos(int x, int y);
	void setMouseButtonPressed(int button);
	void setMouseButtonReleased(int button);
};

}

}

#endif // MOUSE_H
