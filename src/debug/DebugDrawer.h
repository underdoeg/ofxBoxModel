#ifndef DEBUGDRAWER_H
#define DEBUGDRAWER_H

#include "Component.h"
#include "BaseTypes.h"
#include "components/Box.h"
#include "components/Text.h"




namespace boxModel
{

namespace debug
{

struct TextBlockDrawerFont{
	std::vector<ofImage> images;
	int maxFontSize;
	int fontId;
};
	
class TextBlockDrawer : public cppFont::TextBlockDrawer
{
public:
	void setFont(cppFont::Font* font, int fontSize);
	bool allocateFont(cppFont::Font* font, int fontSize);
	void drawCharacter(cppFont::Letter& letter);
	void drawRect(float x, float y, float width, float height);
	void drawLine(float x, float y, float x2, float y2);
	
	//map<int, map<int, std::vector<ofImage> > > images;
	map<int, TextBlockDrawerFont> images;
	std::vector<ofImage>* curImages;
	cppFont::GlyphList* curGlyphList;
};

class DebugDrawer
{
public:
	DebugDrawer();
	~DebugDrawer();
	void draw(core::ComponentContainer* container);
	
	void drawBox(boxModel::components::Box* box);
	void drawText(boxModel::components::Box* box, boxModel::components::Text* text, boxModel::core::Color fg);
	
	boxModel::core::Color color;
	
	TextBlockDrawer textDrawer;
};

}

}

#endif // DEBUGDRAWER_H
