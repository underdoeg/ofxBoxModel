#ifndef BOX_H
#define BOX_H

#include "BoxModel.h"
#include "TreeNode.h"

namespace ofx
{

namespace boxModel
{

namespace core
{

/*******************
 * A Basic box
 ******************/

class Box: public BoxModel, public TreeNode<Box>
{
public:
	Box();
	~Box();
};

}

}

}

#endif // BOX_H
