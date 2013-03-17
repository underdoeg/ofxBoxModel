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
	box->parent = Ptr(this);
	children.push_back(box);
}

void Box::debugDraw()
{
	ofSetColor(100);
	ofRectangle(position, size);
}


void Box::calculateContentSize()
{
}

float Box::getContentHeight()
{
}

float Box::getContentWidth()
{
}

float Box::getHeight()
{
}

float Box::getInnerHeight()
{
}

float Box::getInnerWidth()
{
}

float Box::getOuterHeight()
{
}

float Box::getOuterWidth()
{
}

float Box::getWidth()
{
}

float Box::getX()
{
}

float Box::getY()
{
}

void Box::layout()
{
}

}
}
