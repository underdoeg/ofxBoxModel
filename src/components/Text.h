#ifndef TEXT_H
#define TEXT_H

#include "Component.h" // Base class: boxModel::core::Component
#include "BaseTypes.h"
#include "BoxDefinition.h"
#include "Serializer.h"

namespace boxModel
{

namespace components
{
	
struct TextInfo{
	std::string text;
	float width;
	float height;
	string fontName;
	float fontSize;
	float leading;
	float letterSpacing;
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
	void onBox(Box* box);
	
	core::Value<std::string> text;

	enum TEXT_ALIGNMENT {
	    ALIGN_LEFT,
	    ALIGN_RIGHT,
	    ALIGN_CENTER,
	    ALIGN_JUSTIFY,
	    ALIGN_JUSTIFY_ALL
	};

	core::Value<std::string> fontName;
	core::Unit fontSize;
	core::Unit leading;
	core::Unit wordSpacing;
	core::Unit letterSpacing;
	TEXT_ALIGNMENT textAlignment;
	
	static Nano::signal<void(float&, Text*)> onGetTextBoxHeight;
	
private:
	void pCssFontName(std::string key, std::string value);
	void pCssFontSize(std::string key, std::string value);
	void pCssLeading(std::string key, std::string value);
	void pCssLetterSpacing(std::string key, std::string value);
	void pCssWordSpacing(std::string key, std::string value);
	void pCssTextAlignment(std::string key, std::string value);
	
			
	void onSerializer(Serializer* ser);
	
	void onSerialize(core::VariantList& variants);
	
	void onDeserialize(core::VariantList& variants);
	
	void onAutoWidth(float& width);
	void onAutoHeight(float& height);
	Box* box;
};

}

}

#endif // TEXT_H
