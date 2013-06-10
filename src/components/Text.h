#ifndef TEXT_H
#define TEXT_H

#include "Component.h" // Base class: boxModel::core::Component
#include "BaseTypes.h"
#include "BoxDefinition.h"

namespace boxModel {

namespace components {

class Text : public boxModel::core::Component {
public:
	Text();
	~Text();

	void setup();

	void onBoxDefinition(BoxDefinition* boxDef);
	void onCss(Css* css);


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


private:
	void pCssFontName(std::string key, std::string value);
	void pCssFontSize(std::string key, std::string value);
	void pCssLeading(std::string key, std::string value);
	void pCssLetterSpacing(std::string key, std::string value);
	void pCssWordSpacing(std::string key, std::string value);
	void pCssTextAlignment(std::string key, std::string value);
	
	void onAutoWidth(float& width);
	void onAutoHeight(float& height);
};

}

}

#endif // TEXT_H
