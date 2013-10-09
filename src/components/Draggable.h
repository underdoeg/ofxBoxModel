#ifndef DRAGGABLE_H
#define DRAGGABLE_H

#include "core/Component.h" // Base class: boxModel::core::Component
#include "components/BoxDefinition.h"
#include "components/Mouse.h"

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

	void onMousePress(float mouseX, float mouseY, int button);
	void onMouseDrag(float mouseX, float mouseY, int button);

	Mouse* mouse;
	BoxDefinition* boxDefinition;
};

}}

#endif // DRAGGABLE_H
