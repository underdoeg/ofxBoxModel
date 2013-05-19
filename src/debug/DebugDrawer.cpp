#include "DebugDrawer.h"

namespace boxModel
{

namespace debug
{

using namespace core;


void drawBoxInner(BoxModel* box, Color fg, Color bg)
{
	ofPushStyle();
	
	ofSetColor(fg);
	ofLine(box->position + box->contentPosition, box->position + box->contentPosition + box->contentSize);
	ofLine(box->position + box->contentPosition + core::Point(box->contentSize.x, 0), box->position + box->contentPosition + core::Point(0, box->contentSize.y));

	ofPopStyle();
}

void drawBoxOuter(BoxModel* box, Color fg, Color bg)
{
	ofPushStyle();
	//draw BG
	ofFill();
	ofSetColor(bg);
	ofRect(box->position, box->size.x, box->size.y);

	//draw border
	ofNoFill();
	ofSetColor(fg);
	ofRect(box->position, box->size.x, box->size.y);
	ofPopStyle();
}


}

}
