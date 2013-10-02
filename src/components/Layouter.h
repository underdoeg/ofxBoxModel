#ifndef LAYOUTER_H
#define LAYOUTER_H

#include "core/Component.h"
#include "components/Box.h"
#include "components/Stack.h"
#include "components/BoxDefinition.h"

namespace boxModel {

namespace components {

class Layouter: public core::Component {
public:
	std::string getName();
	
	void setup();

	void onStack(Stack* _stack);

	void onBox(Box* _box);

	void onBoxDefinition(BoxDefinition* box);

	virtual void layout(bool layoutChildren=true);

	Nano::signal<void(std::vector<core::ComponentContainer*>)> overflowed;
	Nano::signal<void()> preLayouted;
	Nano::signal<void()> layouted;
	
	void onFlush();
	
protected:
	virtual void placeBox(Box* childBox);

private:
	void triggerLayout();
	void onContentSizeChanged(core::Point p);
	void onChildRemoved(Stack* child);
	void onChildAdded(Stack* child);
	void onChildFloatingChanged(Floating floating);
	void onChildSizeChanged(core::Point p);
	void onChildPositioningChanged(Position p);
	void onChildUnitChanged(core::Unit* unit);
	void onAutoWidth(float& width);
	void onAutoHeight(float& height);

	core::Point maxContentSize;
	core::Point curPosition;
	float rowMaxHeight;

	std::vector<core::ComponentContainer*> overflowElements;

	Stack* stack;
	Box* box;
	BoxDefinition* boxDefinition;
	bool isDirty;
};

}

}

#endif // LAYOUTER_H
