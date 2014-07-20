#ifndef TEXT_H
#define TEXT_H

#include "Component.h" // Base class: boxModel::core::Component
#include "core/BaseTypes.h"
#include "components/Serializer.h"
#include "core/Utils.h"
#include "TextBlock.h"
#include "components/Linker.h"
#include "components/Splitter.h"
#include "components/Draw.h"
#include "components/Style.h"


namespace boxModel {

namespace components {

struct TextInfo {
	std::string text;
	float width;
	float height;
	string fontName;
	float fontSize;
	float leading;
	float letterSpacing;
	float wordSpacing;
};

class Text : public boxModel::core::Component {
public:
	Text();
	~Text();
	
	static bool setDefaultFont(string path);
	
	std::string getName();

	void setup();

	void copyFrom(Text* text);

	cppFont::TextBlock* getTextBlock();

	core::Value<std::string> text;

	enum TEXT_ALIGNMENT {
	    ALIGN_LEFT,
	    ALIGN_RIGHT,
	    ALIGN_CENTER,
	    ALIGN_JUSTIFY,
	    ALIGN_JUSTIFY_ALL
	};

	enum TEXT_TRANSFORM {
	    TEXT_UPPERCASE,
	    TEXT_LOWERCASE,
	    TEXT_NONE
	};

	static void enableHyphenation(std::string language, std::string folderName = "hyphenation");
	static void disableHyphenation();

	std::string getTextOverflow();

	void getInfo(core::Component::Info& info);

	core::Value<std::string> fontName;
	core::Unit fontSize;
	core::Unit leading;
	core::Unit wordSpacing;
	core::Unit letterSpacing;
	core::Value<TEXT_ALIGNMENT> textAlignment;
	core::Value<TEXT_TRANSFORM> textTransform;

private:
	void update();
	void onFlush();

	void onBoxDefinition(BoxModel* boxDef);
	void onCss(Css* css);
	void onBox(BoxDefinition* box);
	void onLinker(Linker* linker);
	void onDraw(Draw* drawer);

	void onSplitter(Splitter* splitter);
	void onSplitRequested(float x, float y);

	void pCssFontName(std::string key, std::string value);
	void pCssFontSize(std::string key, std::string value);
	void pCssLeading(std::string key, std::string value);
	void pCssLetterSpacing(std::string key, std::string value);
	void pCssWordSpacing(std::string key, std::string value);
	void pCssTextAlignment(std::string key, std::string value);
	void pCssTextTransform(std::string key, std::string value);
	
	void onCssApplyed(Css* css);
	
	void onLinked(Linker* link);

	void onSerializer(Serializer* ser);

	void onStyle(Style* ser);

	void onSerialize(core::VariantList& variants);

	void onDeserialize(core::VariantList& variants);

	void onTextChange(string text);

	void onFontParamChanged(core::Unit* u);

	void onFontSizeChanged(core::Unit* u);
	void onLeadingChanged(core::Unit* u);
	void onWordSpacingChanged(core::Unit* u);
	void onLetterSpacingChanged(core::Unit* u);

	void onAutoWidth(float& width);
	void onAutoHeight(float& height);
	void onWidthChanged(float width);
	void onHeightChanged(float height);
	void onFontNameChanged(std::string fontName);
	void onTextAlignementChanged(TEXT_ALIGNMENT align);

	void drawIt();

	BoxDefinition* box;
	BoxModel* boxDefinition;
	Text* splittedText;
	Draw* drawer;
	Splitter* splitter;
	Style* style;
	Linker* linker;
	cppFont::TextBlock textBlock;
	cppFont::FontFamily fontFamily;

	core::Unit preSplitHeight;

	bool bDrawDirty;
	bool bHasDrawImage;
	unsigned int drawImageId;

	static cppFont::Font defaultFont;
	static bool bHyphenate;
	static string hyphenationLanguage;
	static string hyphenationFolder;
};

}

}

#endif // TEXT_H
