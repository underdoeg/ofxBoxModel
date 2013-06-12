#include "DebugDrawer.h"

#include "components/Stack.h"
#include "components/Style.h"
#include "components/Text.h"

namespace boxModel {

namespace debug {

using namespace boxModel::core;
using namespace boxModel::components;

DebugDrawer::DebugDrawer() {
}

DebugDrawer::~DebugDrawer() {
}

void DebugDrawer::draw(core::ComponentContainer* container) {
	
	if(container->hasComponent<Box>()) {
		Box* box = container->getComponent<Box>();
		drawBox(box);

		if(container->hasComponent<Text>()) {

			Color col = color;
			if(container->hasComponent<Style>()) {
				Style* style = container->getComponent<Style>();
				col = style->getColor();
			}

			Text* text = container->getComponent<Text>();
			drawText(box, text, col);
		}
	}

	if(container->hasComponent<Stack>()) {
		Stack* stack = container->getComponent<Stack>();
		for(Stack* stackChild: stack->getChildren()) {
			draw(stackChild->components);
		}
	}
}

void DebugDrawer::drawText(Box* box, Text* text, Color fg) {

	Point pos = box->getGlobalPosition() + box->contentPosition;
	
	ofSetColor(fg.r,fg.g,fg.b);
	//ofDrawBitmapString(text->text, pos.x, pos.y);

	/*string fontName = text->fontName.get();
	if(ofIsStringInString(fontName,".ttf")) pdf.setFont(ofToDataPath(fontName));
	else pdf.setFont(fontName);

	pdf.setTextAlignment((ofxLibharu::TEXT_ALIGNMENT)text->textAlignment.get());
	pdf.setFontSize(text->fontSize.getValueCalculated());
	pdf.setTextLeading(text->leading.getValueCalculated());
	pdf.setFillColor(fg.r,fg.g,fg.b);
	pdf.setCharSpacing(text->letterSpacing.getValueCalculated());
	pdf.setWordSpacing(text->wordSpacing.getValueCalculated());

	pdf.drawTextBox(text->text, pos.x, pos.y, box->contentSize.x,box->contentSize.y);*/

}

void DebugDrawer::drawBox(Box* box) {

	//
	Style* style;
	if(box->components->hasComponent<Style>()) {
		style = box->components->getComponent<Style>();
	} else {
		style = new Style();
		style->setBgColor(Color(255));
		style->setBorderColor(Color(0));
		style->setColor(color);
	}

	Color color = style->getColor();
	Color bgcol = style->getBgColor();
	Color brdcol = style->getBorderColor();

	//draw fill
	if(style->hasBgColor()) {
		ofFill();
		ofSetColor(bgcol.r,bgcol.g,bgcol.b);
		ofRect(box->getGlobalPosition().x,box->getGlobalPosition().y,box->size.x, box->size.y);
	}

	//
	bool drawBorderTop = false, drawBorderLeft = false, drawBorderRight = false, drawBorderBottom = false;
	float borderTopWidth, borderLeftWidth, borderBottomWidth, borderRightWidth;

	BoxDefinition* boxDef;
	if(box->components->hasComponent<BoxDefinition>()) {
		boxDef = box->components->getComponent<BoxDefinition>();
		if(boxDef->border.top.getType()==Unit::Type_None) drawBorderTop = false;
		else drawBorderTop = true;
		if(boxDef->border.left.getType()==Unit::Type_None) drawBorderLeft = false;
		else drawBorderLeft = true;
		if(boxDef->border.right.getType()==Unit::Type_None) drawBorderRight = false;
		else drawBorderRight = true;
		if(boxDef->border.bottom.getType()==Unit::Type_None) drawBorderBottom = false;
		else drawBorderBottom = true;

		borderTopWidth = boxDef->border.top.getValueCalculated();
		borderLeftWidth = boxDef->border.left.getValueCalculated();
		borderBottomWidth = boxDef->border.bottom.getValueCalculated();
		borderRightWidth = boxDef->border.right.getValueCalculated();
	}

	//draw borders
	ofPushStyle();
	ofFill();
	ofSetColor(brdcol.r,brdcol.g,brdcol.b);

	ofRectangle rect(box->getGlobalPosition().x,box->getGlobalPosition().y, box->size.x, box->size.y);
	if(drawBorderTop) {
		ofRect(rect.getTopLeft().x,rect.getTopLeft().y,rect.width,borderTopWidth);
	}
	if(drawBorderLeft) {
		ofRect(rect.getTopLeft().x,rect.getTopLeft().y,borderLeftWidth,rect.height);
	}
	if(drawBorderRight) {
		ofRect(rect.getTopRight().x-borderRightWidth,rect.getTopRight().y,borderRightWidth,rect.height);
	}
	if(drawBorderBottom) {
		ofRect(rect.getBottomLeft().x,rect.getBottomLeft().y-borderBottomWidth,rect.width,borderBottomWidth);
	}
	ofPopStyle();
	
	//draw debug lines
	ofPushStyle();

	ofSetColor(color);
	ofLine(box->getGlobalPosition() + box->contentPosition, box->getGlobalPosition() + box->contentPosition + box->contentSize);
	ofLine(box->getGlobalPosition() + box->contentPosition + core::Point(box->contentSize.x, 0), box->getGlobalPosition() + box->contentPosition + core::Point(0, box->contentSize.y));

	ofPopStyle();
}

}

}
