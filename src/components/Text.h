#ifndef TEXT_H
#define TEXT_H

#include "Component.h" // Base class: boxModel::core::Component
#include "BaseTypes.h"
#include "BoxDefinition.h"

namespace boxModel
{

namespace components
{
	
struct FontInfo{
	std::string text;
	float width;
	float height;
	string fontName;
	float fontSize;
	float leading;
	float charSpacing;
	float wordSpacing;
};

class Text : public boxModel::core::Component
{
public:
	Text();
	~Text();

	void setup();
	
	void onBoxDefinition(BoxDefinition* boxDef);
	void onCss(Css* css);
	
	core::Value<std::string> text;
	core::Unit leading;
	
	static Nano::signal<void(float&, FontInfo)> onGetTextBoxHeight;

private:
	void pCssLeading(std::string key, std::string value);
	void onAutoWidth(float& width);
	void onAutoHeight(float& height);
};

}

}

#endif // TEXT_H
