#ifndef DEBUGDRAWER_H
#define DEBUGDRAWER_H

#include "Component.h"
#include "BaseTypes.h"
#include "components/Box.h"


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
	
	void drawBoxInner(components::Box* box, core::Color fg, core::Color bg);
	void drawBoxOuter(components::Box* box, core::Color fg, core::Color bg);
	
	static core::Color bgColor;
	static core::Color color;
};

}

}

#endif // DEBUGDRAWER_H
