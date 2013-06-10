#include "DebugDrawer.h"

#include "components/Stack.h"
#include "components/Style.h"
#include "components/Text.h"

namespace boxModel {

namespace debug {

using namespace boxModel::core;
using namespace boxModel::components;

Color DebugDrawer::bgColor = Color(180);
Color DebugDrawer::color = Color(0);

DebugDrawer::DebugDrawer() {
}

DebugDrawer::~DebugDrawer() {
}

void DebugDrawer::draw(core::ComponentContainer* container) {
	//ofPushMatrix();
	if(container->hasComponent<Box>()) {
		Box* box = container->getComponent<Box>();
		if(container->hasComponent<Style>()) {
			Style* style = container->getComponent<Style>();
			if(style->hasBgColor())
				drawBoxOuter(box, style->getBorderColor(), style->getBgColor());
			else {
				ofPushStyle();
				//draw border
				ofNoFill();
				ofSetColor(style->getBorderColor());
				ofRect(box->getGlobalPosition(), box->size.x, box->size.y);
				ofPopStyle();
			}
			drawBoxInner(box, style->getColor(), style->getBgColor());
		} else {
			drawBoxOuter(box, color, bgColor);
			drawBoxInner(box, color, bgColor);
		}
		//ofTranslate(box->contentPosition + box->position);
		if(container->hasComponent<Text>()) {
			Text* text = container->getComponent<Text>();
			ofDrawBitmapString(text->text, box->getGlobalPosition()+Point(0, 20));
		}
	}

	if(container->hasComponent<Stack>()) {
		Stack* stack = container->getComponent<Stack>();
		for(Stack* stackChild: stack->getChildren()) {
			draw(stackChild->components);
		}
	}
	//ofPopMatrix();
}

void DebugDrawer::drawBoxInner(Box* box, core::Color fg, core::Color bg) {
	ofPushStyle();

	ofSetColor(fg);
	ofLine(box->getGlobalPosition() + box->contentPosition, box->getGlobalPosition() + box->contentPosition + box->contentSize);
	ofLine(box->getGlobalPosition() + box->contentPosition + core::Point(box->contentSize.x, 0), box->getGlobalPosition() + box->contentPosition + core::Point(0, box->contentSize.y));

	ofPopStyle();
}

void DebugDrawer::drawBoxOuter(Box* box, core::Color fg, core::Color bg) {
	ofPushStyle();
	//draw BG
	ofFill();
	ofSetColor(bg);
	ofRect(box->getGlobalPosition(), box->size.x, box->size.y);

	//draw border
	ofNoFill();
	ofSetColor(fg);
	ofRect(box->getGlobalPosition(), box->size.x, box->size.y);
	ofPopStyle();
}

}

}
