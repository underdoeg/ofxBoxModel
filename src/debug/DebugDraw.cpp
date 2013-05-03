#include "DebugDraw.h"

namespace ofx
{

namespace boxModel
{

namespace debug
{

using namespace core;
	
DebugDraw::DebugDraw()
{
}

DebugDraw::~DebugDraw()
{
}

void DebugDraw::drawBox(BoxModel* box)
{
	ofPushStyle();
	ofFill();
	ofSetColor(200);
	ofRect(box->position, box->size.x, box->size.y);
	
	ofNoFill();
	ofSetColor(70);
	ofRect(box->position, box->size.x, box->size.y);

	ofLine(box->position + box->contentPosition, box->position + box->contentPosition + box->contentSize);
	ofLine(box->position + box->contentPosition + Point(box->contentSize.x, 0), box->position + box->contentPosition + Point(0, box->contentSize.y));
	ofPopStyle();
}

void DebugDraw::drawTree(core::TreeNodeBase* rootNode)
{
	
}

}

}

}


