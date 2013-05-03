#ifndef LAYOUTER_H
#define LAYOUTER_H

#include "core/TreeNode.h"

namespace ofx
{

namespace boxModel
{

namespace layout
{

class LayouterBase
{
public:

	virtual void layout(core::TreeNodeBase* t) = 0;

};

class Layouter: public LayouterBase
{
public:
	void layout(core::TreeNodeBase* t) {

	}
};

}

}

}

#endif // LAYOUTER_H
