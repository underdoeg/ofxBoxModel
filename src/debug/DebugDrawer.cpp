#include "DebugDrawer.h"

#include "components/Stackable.h"

namespace boxModel
{

namespace debug
{

using namespace core;
using namespace components;
	
Color DebugDrawer::bgColor = Color(180);
Color DebugDrawer::color = Color(0);
	
DebugDrawer::DebugDrawer()
{
}

DebugDrawer::~DebugDrawer()
{
}

void DebugDrawer::draw(core::ComponentContainer* container){
	if(container->hasComponent<Box>()){
		Box* box = container->getComponent<Box>();
		drawBoxOuter(box, color, bgColor);
		drawBoxInner(box, color, bgColor);
	}
	if(container->hasComponent<Stackable>()){
		Stackable* stack = container->getComponent<Stackable>();
		for(Stackable* stackChild: stack->getChildren()){
			draw(stackChild->components);
		}
	}
}

void DebugDrawer::drawBoxInner(Box* box, core::Color fg, core::Color bg)
{
	ofPushStyle();

	ofSetColor(fg);
	ofLine(box->position + box->contentPosition, box->position + box->contentPosition + box->contentSize);
	ofLine(box->position + box->contentPosition + core::Point(box->contentSize.x, 0), box->position + box->contentPosition + core::Point(0, box->contentSize.y));

	ofPopStyle();
}

void DebugDrawer::drawBoxOuter(Box* box, core::Color fg, core::Color bg)
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

