#include "Text.h"

using namespace boxModel::core; 
using namespace std;

namespace boxModel {

namespace components {

Nano::signal<void(float&, Text*)> Text::onGetTextBoxHeight;


Text::Text():boxDefinition(NULL) {
}

Text::~Text() {
}

void Text::setup() {
	text = "undefined";
	fontName = "Times-Roman";
	fontSize = 5;
	leading = 6;
	letterSpacing = 0;
	wordSpacing = 0;
	textAlignment = ALIGN_LEFT;
	textTransform = TEXT_NONE;
	
	LISTEN_FOR_COMPONENT(BoxDefinition, Text, onBoxDefinition)
	LISTEN_FOR_COMPONENT(Css, Text, onCss)
	LISTEN_FOR_COMPONENT(Box, Text, onBox)
	LISTEN_FOR_COMPONENT(Serializer, Text, onSerializer)

	text.changed.connect<Text, &Text::onTextChange>(this);
	
	fontSize.changed.connect<Text, &Text::onFontParamChanged>(this);
	leading.changed.connect<Text, &Text::onFontParamChanged>(this);
	letterSpacing.changed.connect<Text, &Text::onFontParamChanged>(this);
	wordSpacing.changed.connect<Text, &Text::onFontParamChanged>(this);
}

void Text::onBox(Box* b){
	box = b;
}

void Text::onCss(Css* css){
	css->addCssParserFunction<Text, &Text::pCssFontName>("font-name", this);
	css->addCssParserFunction<Text, &Text::pCssFontSize>("font-size", this);
	css->addCssParserFunction<Text, &Text::pCssLeading>("line-height", this);
	css->addCssParserFunction<Text, &Text::pCssLeading>("leading", this);
	css->addCssParserFunction<Text, &Text::pCssLetterSpacing>("letter-spacing", this);
	css->addCssParserFunction<Text, &Text::pCssWordSpacing>("word-spacing", this);
	css->addCssParserFunction<Text, &Text::pCssTextAlignment>("text-align", this);
	css->addCssParserFunction<Text, &Text::pCssTextTransform>("text-transform", this);
}

void Text::onTextChange(string _text){
	if(textTransform==TEXT_NONE) text = _text;
	if(textTransform==TEXT_LOWERCASE) text = stringToLower(_text);
	if(textTransform==TEXT_UPPERCASE) text = stringToUpper(_text);
	if(boxDefinition != NULL){
		boxDefinition->recalculateBoxSize();
	}
}

void Text::onFontParamChanged(Unit* u)
{
	if(boxDefinition == NULL)
		return;
	if(boxDefinition->height == Unit::Auto)
		boxDefinition->recalculateBoxSize();
}

void Text::onBoxDefinition(BoxDefinition* bd){
	boxDefinition = bd;
	boxDefinition->onHeightAuto.connect<Text, &Text::onAutoHeight>(this);
	boxDefinition->onWidthAuto.connect<Text, &Text::onAutoWidth>(this);
}

void Text::pCssFontName(std::string key, std::string value){
	fontName = value;
}

void Text::pCssFontSize(std::string key, std::string value){
	fontSize = core::Unit::parseCssNumber(value);
}

void Text::pCssLeading(std::string key, std::string value){
	leading = core::Unit::parseCssNumber(value);
}

void Text::pCssLetterSpacing(std::string key, std::string value){
	letterSpacing = core::Unit::parseCssNumber(value);
}

void Text::pCssWordSpacing(std::string key, std::string value){
	wordSpacing = core::Unit::parseCssNumber(value);
}

void Text::pCssTextAlignment(std::string key, std::string value){
	
	if(value=="left") textAlignment = ALIGN_LEFT;
	if(value=="right") textAlignment = ALIGN_RIGHT;
	if(value=="center") textAlignment = ALIGN_CENTER;
	if(value=="justify") textAlignment = ALIGN_JUSTIFY;
	if(value=="justify_all" || value=="justify-all") textAlignment = ALIGN_JUSTIFY_ALL;
}

void Text::pCssTextTransform(std::string key, std::string value){
	
	if(value=="uppercase") textTransform = TEXT_UPPERCASE;
	if(value=="lowercase") textTransform = TEXT_LOWERCASE;
	if(value=="none") textTransform = TEXT_NONE;
	
	onTextChange(text);
}

void Text::onAutoWidth(float& width){
	
}

void Text::onAutoHeight(float& height){
	cout << "LOOKING FOR AUTO HEIGHT" << endl;
	if(box == NULL)
		return;
	onGetTextBoxHeight(height, this);
	cout << height << endl;
}

/******************************************************************************************/

void Text::onSerializer(Serializer* ser) {
	ser->deserialized.connect<Text, &Text::onDeserialize>(this);
	ser->serialized.connect<Text, &Text::onSerialize>(this);
}

void Text::onSerialize(core::VariantList& variants) {
	variants.set("text", text);
}

void Text::onDeserialize(core::VariantList& variants) {
	if(variants.hasKey("text")){
		text = variants.get("text");
	}
}

} //end namespace

}

