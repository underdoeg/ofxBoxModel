#include "Text.h"
#include "Globals.h"

using namespace boxModel::core;
using namespace std;
using namespace boxModel::components;

//////////////////////////////////////////////////////////////////////////////////
/*
class TextDrawer: public cppFont::TextBlockDrawer {
public:
	bool allocateFont(Font* font, int fontSize) {
		return true;
	}

	void drawCharacter(cppFont::Letter& letter) {

	}

	void drawLine(float x, float y, float x2, float y2) {

	}

	void drawRect(float x, float y, float width, float height) {

	}

	void setFont(cppFont::Font* font, int fontSize) {

	}
};

TextDrawer textDrawer;
*/
//////////////////////////////////////////////////////////////////////////////////

cppFont::Font Text::defaultFont("/usr/share/fonts/TTF/andalemo.ttf");
//cppFont::Font Text::defaultFont("/usr/share/fonts/cantarell/Cantarell-Regular.otf");

bool Text::bHyphenate;
string Text::hyphenationLanguage;
string Text::hyphenationFolder;

void Text::enableHyphenation(std::string language, std::string folder) {
	hyphenationLanguage = language;
	hyphenationFolder = folder;
	bHyphenate = true;
}

void Text::disableHyphenation() {
	bHyphenate = false;
}

///////////////////////////////////////////////////////////////////////////////
Text::Text():boxDefinition(NULL) {
}

Text::~Text() {
}

bool Text::setDefaultFont(string path)
{
	defaultFont = cppFont::Font(Globals::get().dataRoot+path);
	return defaultFont.isLoaded;
}

std::string Text::getName() {
	return "text";
}

void Text::setup() {
	if(bHyphenate) {
		textBlock.enableHyphenation(hyphenationLanguage, Globals::get().dataRoot+hyphenationFolder+"/");
	}

	style = NULL;
	linker = NULL;

	update();
	bHasDrawImage = false;
	bDrawDirty = true;

	fontFamily.setFontNormal(&defaultFont);
	textBlock.setFontFamily(&fontFamily);

	fontSize.changed.connect<Text, &Text::onFontSizeChanged>(this);
	leading.changed.connect<Text, &Text::onLeadingChanged>(this);
	letterSpacing.changed.connect<Text, &Text::onLetterSpacingChanged>(this);
	wordSpacing.changed.connect<Text, &Text::onWordSpacingChanged>(this);
	fontName.changed.connect<Text, &Text::onFontNameChanged>(this);
	textAlignment.changed.connect<Text, &Text::onTextAlignementChanged>(this);


	text = "undefined";
	//fontName = defaultFont.filePath;
	fontSize = 10;
	//leading = 6;
	letterSpacing = 0;
	wordSpacing = 0;
	textAlignment = ALIGN_LEFT;
	textTransform = TEXT_NONE;

	LISTEN_FOR_COMPONENT(BoxModel, Text, onBoxDefinition)
	LISTEN_FOR_COMPONENT(Css, Text, onCss)
	LISTEN_FOR_COMPONENT(BoxDefinition, Text, onBox)
	LISTEN_FOR_COMPONENT(Serializer, Text, onSerializer)
	LISTEN_FOR_COMPONENT(Linker, Text, onLinker)
	LISTEN_FOR_COMPONENT(Splitter, Text, onSplitter)
	LISTEN_FOR_COMPONENT(Draw, Text, onDraw)
	LISTEN_FOR_COMPONENT(Style, Text, onStyle)

	text.changed.connect<Text, &Text::onTextChange>(this);
}

void Text::update() {
	bDrawDirty = true;
}

void Text::onFlush() {
	if(linker != NULL) {
		//if(textBlock.hasOverflow()) {
		Linker* linkTo = linker->getLinkTo();
		if(linkTo != NULL) {
			if(linkTo->components->hasComponent<Text>()) {
				linkTo->components->getComponent<Text>()->text = textBlock.getOverflow();
				//linkTo->components->getComponent<Text>()->onFlush();
			}
		}
		//}
	}
}

void Text::copyFrom(Text* t) {
	fontName = t->fontName;
	leading = t->leading;
	text = t->text;
	fontSize = t->fontSize;
	letterSpacing = t->letterSpacing;
	wordSpacing = t->wordSpacing;
	textAlignment = t->textAlignment;
	textTransform = t->textTransform;
}

void Text::onBox(BoxDefinition* b) {
	box = b;
	box->contentSize.x.changed.connect<Text, &Text::onWidthChanged>(this);
	onWidthChanged(box->contentSize.x);
	box->contentSize.y.changed.connect<Text, &Text::onHeightChanged>(this);
	onHeightChanged(box->contentSize.y);
}

void Text::onCss(Css* css) {
	css->cssApplyed.connect<Text, &Text::onCssApplyed>(this);

	css->addCssParserFunction<Text, &Text::pCssFontName>("font-name", this);
	css->addCssParserFunction<Text, &Text::pCssFontName>("font-family", this);
	css->addCssParserFunction<Text, &Text::pCssFontName>("font", this);

	css->addCssParserFunction<Text, &Text::pCssFontSize>("font-size", this);
	css->addCssParserFunction<Text, &Text::pCssLeading>("line-height", this);
	css->addCssParserFunction<Text, &Text::pCssLeading>("leading", this);
	css->addCssParserFunction<Text, &Text::pCssLetterSpacing>("letter-spacing", this);
	css->addCssParserFunction<Text, &Text::pCssWordSpacing>("word-spacing", this);
	css->addCssParserFunction<Text, &Text::pCssTextAlignment>("text-align", this);
	css->addCssParserFunction<Text, &Text::pCssTextTransform>("text-transform", this);
}

void Text::onTextChange(string _text) {
	_text = stringTrim(_text);
	if(textTransform==TEXT_NONE) text = _text;
	if(textTransform==TEXT_LOWERCASE) text = stringToLower(_text);
	if(textTransform==TEXT_UPPERCASE) text = stringToUpper(_text);
	textBlock.setText(text);
	update();
}

void Text::onFontParamChanged(Unit* u) {
}

void Text::onBoxDefinition(BoxModel* bd) {
	boxDefinition = bd;
	boxDefinition->onHeightAuto.connect<Text, &Text::onAutoHeight>(this);
	boxDefinition->onWidthAuto.connect<Text, &Text::onAutoWidth>(this);
}

void Text::pCssFontName(std::string key, std::string value) {
	value = stringReplace(value, "\"", "");
	fontName = value;
}

void Text::pCssFontSize(std::string key, std::string value) {
	fontSize = core::Unit::parseCssNumber(value);
	//update();
}

void Text::pCssLeading(std::string key, std::string value) {
	leading = core::Unit::parseCssNumber(value);
	//update();
}

void Text::pCssLetterSpacing(std::string key, std::string value) {
	letterSpacing = core::Unit::parseCssNumber(value);
	//update();
}

void Text::pCssWordSpacing(std::string key, std::string value) {
	wordSpacing = core::Unit::parseCssNumber(value);
	//update();
}

void Text::pCssTextAlignment(std::string key, std::string value) {
	if(value=="left") textAlignment = ALIGN_LEFT;
	else if(value=="right") textAlignment = ALIGN_RIGHT;
	else if(value=="center") textAlignment = ALIGN_CENTER;
	else if(value=="justify") textAlignment = ALIGN_JUSTIFY;
	else if(value=="justify_all" || value=="justify-all") textAlignment = ALIGN_JUSTIFY_ALL;
	//update();
}

void Text::pCssTextTransform(std::string key, std::string value) {

	if(value=="uppercase") textTransform = TEXT_UPPERCASE;
	if(value=="lowercase") textTransform = TEXT_LOWERCASE;
	if(value=="none") textTransform = TEXT_NONE;

	onTextChange(text);
}

void Text::onHeightChanged(float height) {
	if(boxDefinition != NULL) {
		if(boxDefinition->width == Unit::Auto) {
			textBlock.setWidthAuto(true);
		}
		if(boxDefinition->height == Unit::Auto) {
			textBlock.setHeightAuto(true);
			return;
		}
	}
	textBlock.setHeight(height);
	update();
}

void Text::onWidthChanged(float width) {
	if(boxDefinition != NULL) {
		if(boxDefinition->height == Unit::Auto) {
			textBlock.setHeightAuto(true);
		}
		if(boxDefinition->width == Unit::Auto) {
			textBlock.setWidthAuto(true);
			return;
		}
	}
	textBlock.setWidth(width);
	update();
}

void Text::onFontSizeChanged(core::Unit* u) {
	textBlock.setFontSize(u->getValueCalculated());
	if(boxDefinition != NULL) {
		boxDefinition->recalculateBoxSize();
	}
	update();
}

void Text::onLeadingChanged(core::Unit* u) {
	textBlock.setLeading(u->getValueCalculated());
	if(boxDefinition != NULL) {
		boxDefinition->recalculateBoxSize();
	}
	update();
}

void Text::onLetterSpacingChanged(core::Unit* u) {
	textBlock.setLetterSpacing(u->getValueCalculated());
	if(boxDefinition != NULL) {
		boxDefinition->recalculateBoxSize();
	}
	update();
}

void Text::onWordSpacingChanged(core::Unit* u) {
	textBlock.setWordSpacing(u->getValueCalculated());
	if(boxDefinition != NULL) {
		boxDefinition->recalculateBoxSize();
	}
	update();
}

void Text::onFontNameChanged(std::string fontName) {
	if(fontName == "")
		return;
	fontFamily.loadNormal(Globals::get().dataRoot+fontName);
	textBlock.setDirty();
	update();
}

void Text::onTextAlignementChanged(TEXT_ALIGNMENT align) {
	switch(align) {
	case ALIGN_CENTER:
	textBlock.setAlign(cppFont::TextBlock::Center);
	break;
	case ALIGN_LEFT:
	textBlock.setAlign(cppFont::TextBlock::Left);
	break;
	default:
	debug::warning("alignement not supported yet");
	}
	update();
}

void Text::onAutoWidth(float& width) {
	textBlock.setWidthAuto(true);
	//TODO: necessary?
	//
	textBlock.setDirty();
	float _width = textBlock.getWidth();
	if(_width > width)
		width = _width;
}

void Text::onAutoHeight(float& height) {
	if(textBlock.getHeight() > height)
		height = textBlock.getHeight();
}

void Text::onCssApplyed(Css* css) {

}

/******************************************************************************************/

void Text::onLinker(Linker* l) {
	linker = l;
	linker->linkedTo.connect<Text, &Text::onLinked>(this);
}

void Text::onStyle(Style* s) {
	style = s;
}

void Text::onDraw(Draw* d) {
	drawer = d;
	drawer->onDraw.connect<Text, &Text::drawIt>(this);
}

void Text::drawIt() {
	//check if something has changed
	if(bDrawDirty) {
		if(bHasDrawImage) {
			boxModel::core::RendererResources::removeImage(drawImageId);
		}
		cppFont::TextBlockImage img = textBlock.getAsImage();

		boxModel::core::Color color(255, 255, 255);
		if(style)
			color = style->getColor();

		//create a colored image with an alpha channel
		unsigned char* pixels = new unsigned char[img.width*img.height*4];
		unsigned int iAlpha = 0;
		for(unsigned int i=0; i< img.width*img.height*4; i+=4) {
			pixels[i] = color.r;
			pixels[i+1] = color.g;
			pixels[i+2] = color.b;
			pixels[i+3] = img.pixels[iAlpha];
			iAlpha++;
		}

		//cleanup
		delete[] img.pixels;

		drawImageId = boxModel::core::RendererResources::addImage(pixels, img.width, img.height, 4);
		bHasDrawImage = true;
		bDrawDirty = false;
	}

	Draw::getRenderer()->drawImage(drawImageId);
}

void Text::onLinked(Linker* link) {

}

void Text::onSerializer(Serializer* ser) {
	ser->deserialized.connect<Text, &Text::onDeserialize>(this);
	ser->serialized.connect<Text, &Text::onSerialize>(this);
}

void Text::onSerialize(core::VariantList& variants) {
	variants.set("text", text);
}

void Text::onDeserialize(core::VariantList& variants) {
	if(variants.hasKey("text")) {
		text = variants.get("text");
	}
}

cppFont::TextBlock* Text::getTextBlock() {
	return &textBlock;
}

std::string Text::getTextOverflow() {
	return textBlock.getOverflow();
}

void Text::onSplitter(Splitter* spl) {
	splitter = spl;
	splitter->splitRequested.connect<Text, &Text::onSplitRequested>(this);
}

void Text::onSplitRequested(float x, float y) {

	if(boxDefinition != NULL) {

		if(textBlock.getNumLines() > 1) {
			//ok, we have more than one line, so it is ok to split
			std::vector<ComponentContainer*> clones = splitter->makeSplit();

			if(clones.size()==2) {

				Text* t1 = clones[0]->getComponent<Text>();

				//cout << t1->getTextOverflow() << endl;
				clones[1]->getComponent<Text>()->text = t1->getTextOverflow();
				//clones[1]->getComponent<Text>()->text = "HELLO";

				if(boxDefinition != NULL) {
					//we set the height explicitely to the height of the text field, because of the line height the splitted height is too short
					clones[1]->getComponent<BoxModel>()->height = clones[1]->getComponent<Text>()->getTextBlock()->getHeight();
				}
			}
		}
	}
}

void Text::getInfo(core::Component::Info& info) {

}

