#ifndef BOX_H
#define BOX_H

#include "BoxModel.h"
#include "TreeNode.h"
#include "Addressable.h"
#include "Styleable.h"
#include "Layoutable.h"
#include "css/CssLoadable.h"

namespace ofx
{

namespace boxModel
{

namespace core
{

/*******************
 * A Basic box
 ******************/

class Box: public BoxModel, public TreeNode<Box>, public Addressable<Box>, public Styleable<Box>, public Layoutable<Box>, public css::CssLoadable<Box>
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
