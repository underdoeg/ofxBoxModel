#ifndef BOX_H
#define BOX_H

#include "BoxModel.h"
#include "TreeNode.h"
#include "html/Addressable.h"

namespace ofx
{

namespace boxModel
{

namespace core
{

/*******************
 * A Basic box
 ******************/

class Box: public BoxModel, public TreeNode<Box>, public html::Addressable<Box>
{
public:
	Box();
	~Box();
	string type;
};

}

}

}

#endif // BOX_H
