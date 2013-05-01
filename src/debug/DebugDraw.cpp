#include "DebugDraw.h"

namespace ofx
{

namespace boxModel
{

namespace debug
{

DebugDraw::DebugDraw()
{
}

DebugDraw::~DebugDraw()
{
}

void DebugDraw::drawBox(core::BoxModel* box)
{
	/*
	ofPushStyle();
	ofFill();
	ofSetColor(200);
	ofRect(box->position, size.x, size.y);
	ofNoFill();
	ofSetColor(70);
	ofRect(position, size.x, size.y);

	ofLine(position + contentPosition, position + contentPosition + contentSize);
	ofLine(position + contentPosition + Point(contentSize.x, 0), position + contentPosition + Point(0, contentSize.y));
	ofPopStyle();
	*/
}

void DebugDraw::drawTree(core::TreeNodeBase* rootNode)
{
}

}

}

}


