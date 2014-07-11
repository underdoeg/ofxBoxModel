#ifndef LAYOUTER_H
#define LAYOUTER_H

#include "core/Component.h"
#include "components/BoxDefinition.h"
#include "components/Stack.h"
#include "components/BoxModel.h"
#include "components/Style.h"


namespace boxModel {

namespace components {

class Layouter: public core::Component {
public:
	std::string getName();
	
	void setup();

	void onStack(Stack* _stack);

	void onBox(BoxDefinition* _box);

	void onBoxDefinition(BoxModel* box);

	virtual void layout(bool layoutChildren=true);

	void setLayoutable(bool state);

	Nano::Signal<void(std::vector<core::ComponentContainer*>)> overflowed;
	Nano::Signal<void()> preLayouted;
	Nano::Signal<void()> layouted;
	
	void onFlush();
	void getInfo(core::Component::Info& info);

protected:
	virtual void placeBox(BoxDefinition* childBox);

private:
	void triggerLayout();
	void onContentSizeChanged(core::Point p);
	void onChildRemoved(Stack* child);
	void onChildAdded(Stack* child);
	void onChildFloatingChanged(Floating floating);
	void onChildSizeChanged(core::Point p);
	void onChildPositioningChanged(Position p);
	void onChildUnitChanged(core::Unit* unit);
	void onChildDisplayChanged(Style::DisplayType dt);
	void onAutoWidth(float& width);
	void onAutoHeight(float& height);

	core::Point maxContentSize;
	core::Point curPosition;
	float rowMaxHeight;

	std::vector<core::ComponentContainer*> overflowElements;

	Nano::Signal<void()> layoutTriggered;

	bool doLayouting;
	Stack* stack;
	BoxDefinition* box;
	BoxModel* boxDefinition;
	bool isLayoutDirty;
};

}

}

#endif // LAYOUTER_H
