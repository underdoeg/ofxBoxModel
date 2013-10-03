#include "DebugDrawer.h"

#include "components/Stack.h"
#include "components/Style.h"
#include "components/Text.h"
#include "components/Mouse.h"

using namespace boxModel::core;
using namespace boxModel::components;
using namespace boxModel::debug;

DebugDrawer::DebugDrawer() {
}

DebugDrawer::~DebugDrawer() {
}

void DebugDrawer::draw(core::ComponentContainer* container) {
	if(container->hasComponent<Splitter>()){
		if(container->getComponent<Splitter>()->hasSplits)
			return;
	}
	if(container->hasComponent<BoxDefinition>()) {
		BoxDefinition* box = container->getComponent<BoxDefinition>();
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

void DebugDrawer::drawText(BoxDefinition* box, Text* text, Color fg) {

	Point pos = box->getGlobalPosition() + box->contentPosition;
	
	ofSetColor(fg.r,fg.g,fg.b);
		
	ofPushMatrix();
	
	ofTranslate(pos);
	
	text->getTextBlock()->draw(&textDrawer);
	
	ofPopMatrix();
}

void DebugDrawer::drawBox(BoxDefinition* box) {

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
		ofRect(box->getGlobalPosition().x, box->getGlobalPosition().y, box->size.x, box->size.y);
	}

	//
	bool drawBorderTop = false, drawBorderLeft = false, drawBorderRight = false, drawBorderBottom = false;
	float borderTopWidth, borderLeftWidth, borderBottomWidth, borderRightWidth;

	BoxModel* boxDef;
	if(box->components->hasComponent<BoxModel>()) {
		boxDef = box->components->getComponent<BoxModel>();
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
	
	/*
	if(box->components->hasComponent<Mouse>()){
		
		Mouse* mouse = box->components->getComponent<Mouse>();
		
		ofPushStyle();
		
		ofSetColor(255, 0, 0);
		ofCircle(box->getGlobalPosition().x + box->contentPosition.x + mouse->mousePos.x, box->getGlobalPosition().y + box->contentPosition.y + mouse->mousePos.y, 3, 3);
	
		ofPopStyle();
	
	}
	*/
}


/************************ TEXT BLOCK **********************************/

bool TextBlockDrawer::allocateFont(cppFont::Font* font, int fontSize) {
	int fontSizeToStore = fontSize*2;
	if(images[font->id].maxFontSize >= fontSizeToStore)
		return true;
	cppFont::GlyphList& glyphs = font->getGlyphList(fontSizeToStore);
	images[font->id].maxFontSize = fontSizeToStore;
	images[font->id].images.resize(glyphs.size());
	for(std::vector<cppFont::Glyph>::iterator it = glyphs.begin(); it < glyphs.end(); it++) {
		cppFont::Glyph& glyph = *it;
		if(glyph.bitmapWidth > 0 && glyph.bitmapHeight > 0) {
			ofImage& img = images[font->id].images[glyph.charIndex];
			//img.setFromPixels(glyph.bitmap, glyph.bitmapWidth, glyph.bitmapHeight, OF_IMAGE_GRAYSCALE);
			ofPixels pixels;
			pixels.setFromPixels(glyph.bitmap, glyph.bitmapWidth, glyph.bitmapHeight, OF_IMAGE_GRAYSCALE);
			img.allocate(glyph.bitmapWidth, glyph.bitmapHeight, OF_IMAGE_COLOR_ALPHA);
			img.getPixelsRef().setChannel(0, pixels);
			img.getPixelsRef().setChannel(1, pixels);
			img.getPixelsRef().setChannel(2, pixels);
			img.getPixelsRef().setChannel(3, pixels);
			img.reloadTexture();
		}
	}
	return true;
}

void TextBlockDrawer::setFont(cppFont::Font* font, int fontSize) {
	curImages = &images[font->id].images;
}

void TextBlockDrawer::drawCharacter(cppFont::Letter& letter) {
	if(curImages ==  NULL)
		return;
	/*
	if(letter.glyph->charIndex >= curImages->size())
		return;
	*/
		
	ofImage& img = curImages->at(letter.glyph->charIndex);
	if(img.isAllocated())
		img.draw(letter.x, letter.y - letter.glyph->bitmapHeight + letter.glyph->offsetY, letter.glyph->bitmapWidth, letter.glyph->bitmapHeight);
}

void TextBlockDrawer::drawRect(float x, float y, float width, float height) {
	ofNoFill();
	ofRect(x, y, width, height);
}

void TextBlockDrawer::drawLine(float x, float y, float x2, float y2) {
	ofLine(x, y, x2, y2);
}

