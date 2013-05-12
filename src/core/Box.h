#ifndef BOX_H
#define BOX_H

#include "BoxModel.h"
#include "TreeNode.h"
#include "core/Addressable.h"

namespace ofx
{

namespace boxModel
{

namespace core
{

/*******************
 * A Basic box
 ******************/

class Box: public BoxModel, public TreeNode<Box>, public Addressable<Box>
{
public:
	Box();
	~Box();
	
	virtual std::string getType();
private:
};

}

}

}

#endif // BOX_H
