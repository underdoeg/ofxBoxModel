#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "core/BoxModel.h"
#include "core/TreeNode.h"

namespace ofx
{

namespace boxModel
{

namespace debug
{

class DebugDraw
{
public:
	static void drawTree(core::TreeNodeBase* rootNode);
	static void drawBox(core::BoxModel* box);

private:
	DebugDraw();
	~DebugDraw();

};

}

}

}

#endif // DEBUGDRAW_H
