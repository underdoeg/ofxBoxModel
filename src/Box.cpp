#include "Box.h"


namespace ofx
{
namespace BoxModel
{

Box::Box()
{

}

Box::~Box()
{
}

void Box::add(Box::Ptr box)
{
	children.push_back(box);
}

void Box::debugDraw()
{
	ofRectangle(x, y, width, height);
}

}
}
