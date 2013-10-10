#ifndef DRAGGABLE_H
#define DRAGGABLE_H

#include "core/Component.h" // Base class: boxModel::core::Component
#include "components/BoxDefinition.h"
#include "components/Mouse.h"
#include "components/BoxModel.h"
#include "components/Stack.h"

namespace boxModel
{

namespace components
{

class Draggable : public boxModel::core::Component
{
public:
	Draggable();
	~Draggable();

	void setup();

	std::string getName();

private:
	void onMouse(Mouse* m);
	void onBoxDefinition(BoxDefinition* bd);
	void onBoxModel(BoxModel* bd);
	void onStack(Stack* s);

	void onMousePress(float mouseX, float mouseY, int button);
	void onMouseDrag(float mouseX, float mouseY, boxModel::components::Mouse::ButtonStates& bt);

	bool bDragging;
	bool bLimitToParent;
	boxModel::core::Point lastPos;

	Mouse* mouse;
	BoxDefinition* boxDefinition;
	BoxModel* boxModel;
	Stack* stack;
};

}}

#endif // DRAGGABLE_H
