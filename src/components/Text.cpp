#include "Text.h"
#include "Globals.h"

using namespace boxModel::core; 
using namespace std;

using namespace boxModel::components;

cppFont::Font Text::defaultFont("/usr/share/fonts/TTF/arial.ttf");

bool Text::bHyphenate;
string Text::hyphenationLanguage;
string Text::hyphenationFolder;

void Text::enableHyphenation(std::string language, std::string folder)
{
	hyphenationLanguage = language;
	hyphenationFolder = folder;
	bHyphenate = true;
}

void Text::disableHyphenation(){
	bHyphenate = false;
}

///////////////////////////////////////////////////////////////////////////////
Text::Text():boxDefinition(NULL) {
}

Text::~Text() {
}

std::string Text::getName(){
	return "text";
}

void Text::setup() {
	if(bHyphenate){
		textBlock.enableHyphenation(hyphenationLanguage, Globals::get().dataRoot+hyphenationFolder+"/");
	}
	
	fontFamily.setFontNormal(&defaultFont);
	textBlock.setFontFamily(&fontFamily);
	
	fontSize.changed.connect<Text, &Text::onFontSizeChanged>(this);
	leading.changed.connect<Text, &Text::onLeadingChanged>(this);
	letterSpacing.changed.connect<Text, &Text::onLetterSpacingChanged>(this);
	wordSpacing.changed.connect<Text, &Text::onWordSpacingChanged>(this);
	fontName.changed.connect<Text, &Text::onFontNameChanged>(this);

	
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

	text.changed.connect<Text, &Text::onTextChange>(this);
}

void Text::copyFrom(Text* t)
{
	fontName = t->fontName;
	leading = t->leading;
	text = t->text;
	fontSize = t->fontSize;
	letterSpacing = t->letterSpacing;
	wordSpacing = t->wordSpacing;
	textAlignment = t->textAlignment;
	textTransform = t->textTransform;
}

void Text::onBox(BoxDefinition* b){
	box = b;
	box->contentSize.x.changed.connect<Text, &Text::onWidthChanged>(this);
	onWidthChanged(box->contentSize.x);
	box->contentSize.y.changed.connect<Text, &Text::onHeightChanged>(this);
	onHeightChanged(box->contentSize.y);
}

void Text::onCss(Css* css){
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

void Text::onTextChange(string _text){
	_text = stringTrim(_text);
	if(textTransform==TEXT_NONE) text = _text;
	if(textTransform==TEXT_LOWERCASE) text = stringToLower(_text);
	if(textTransform==TEXT_UPPERCASE) text = stringToUpper(_text);
	textBlock.setText(text);
}

void Text::onFontParamChanged(Unit* u)
{
}

void Text::onBoxDefinition(BoxModel* bd){
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

void Text::onHeightChanged(float height)
{
	if(boxDefinition != NULL){
		if(boxDefinition->width == Unit::Auto){
			textBlock.setWidthAuto(true);
		}
		if(boxDefinition->height == Unit::Auto){
			textBlock.setHeightAuto(true);
			return;
		}
	}
	textBlock.setHeight(height);
}

void Text::onWidthChanged(float width)
{
	if(boxDefinition != NULL){
		if(boxDefinition->height == Unit::Auto){
			textBlock.setHeightAuto(true);
			
		}
		if(boxDefinition->width == Unit::Auto){
			textBlock.setWidthAuto(true);
			return;
		}
	}
	textBlock.setWidth(width);
}

void Text::onFontSizeChanged(core::Unit* u)
{
	textBlock.setFontSize(u->getValueCalculated());
	if(boxDefinition != NULL){
		boxDefinition->recalculateBoxSize();
	}
}

void Text::onLeadingChanged(core::Unit* u)
{
	textBlock.setLeading(u->getValueCalculated());
	if(boxDefinition != NULL){
		boxDefinition->recalculateBoxSize();
	}
}

void Text::onLetterSpacingChanged(core::Unit* u)
{
	textBlock.setLetterSpacing(u->getValueCalculated());
	if(boxDefinition != NULL){
		boxDefinition->recalculateBoxSize();
	}
}

void Text::onWordSpacingChanged(core::Unit* u)
{
	textBlock.setWordSpacing(u->getValueCalculated());
	if(boxDefinition != NULL){
		boxDefinition->recalculateBoxSize();
	}
}

void Text::onFontNameChanged(std::string fontName)
{
	fontFamily.loadNormal(Globals::get().dataRoot+fontName);
	textBlock.setDirty();
}

void Text::onAutoWidth(float& width){
	width = textBlock.getWidth();
}

void Text::onAutoHeight(float& height){
	height = textBlock.getHeight();
}

/******************************************************************************************/

void Text::onLinker(Linker* linker)
{
	linker->linkedTo.connect<Text, &Text::onLinked>(this);
}

void Text::onLinked(Linker* link)
{
}

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

cppFont::TextBlock* Text::getTextBlock()
{
	return &textBlock;
}

std::string Text::getTextOverflow()
{
	return textBlock.getOverflow();
}

void Text::onSplitter(Splitter* spl)
{
	splitter = spl;
	splitter->splitRequested.connect<Text, &Text::onSplitRequested>(this);
}

void Text::onSplitRequested(float x, float y)
{

	if(boxDefinition != NULL){

		if(textBlock.getNumLines() > 1){
			//ok, we have more than one line, so it is ok to split
			std::vector<ComponentContainer*> clones = splitter->makeSplit();

			if(clones.size()==2){
				
				Text* t1 = clones[0]->getComponent<Text>();
				
				//cout << t1->getTextOverflow() << endl;
				clones[1]->getComponent<Text>()->text = t1->getTextOverflow();
				//clones[1]->getComponent<Text>()->text = "HELLO";
				
				if(boxDefinition != NULL){
					//we set the height explicitely to the height of the text field, because of the line height the splitted height is too short
					clones[1]->getComponent<BoxModel>()->height = clones[1]->getComponent<Text>()->getTextBlock()->getHeight();
				}
			}
		}
	}
}

void Text::getInfo(core::Component::Info& info){

}