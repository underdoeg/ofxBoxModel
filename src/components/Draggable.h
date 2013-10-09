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
};

}}

#endif // DRAGGABLE_H
