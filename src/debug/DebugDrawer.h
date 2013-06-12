#ifndef DEBUGDRAWER_H
#define DEBUGDRAWER_H

#include "Component.h"
#include "BaseTypes.h"
#include "components/Box.h"
#include "components/Text.h"


using namespace boxModel::core;
using namespace boxModel::components;

namespace boxModel
{

namespace debug
{

class DebugDrawer
{
public:
	DebugDrawer();
	~DebugDrawer();
	void draw(core::ComponentContainer* container);
	
	void drawBox(Box* box);
	void drawText(Box* box, Text* text, Color fg);
	
	Color color;
};

}

}

#endif // DEBUGDRAWER_H
