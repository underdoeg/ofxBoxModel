#include "Text.h"

namespace boxModel
{

namespace components
{

Text::Text()
{
}

Text::~Text()
{
}

void Text::setup()
{
	text = "undefined";
	fontName = "Times-Roman";
	fontSize = 5;
	leading = 6;
	letterSpacing = 0;
	wordSpacing = 0;
	textAlignment = ALIGN_LEFT;
	
	LISTEN_FOR_COMPONENT(BoxDefinition, Text, onBoxDefinition)
	LISTEN_FOR_COMPONENT(Css, Text, onCss)
}

void Text::onCss(Css* css){
	
	css->addCssParserFunction<Text, &Text::pCssFontName>("font-name", this);
	css->addCssParserFunction<Text, &Text::pCssFontSize>("font-size", this);
	css->addCssParserFunction<Text, &Text::pCssLeading>("line-height", this);
	css->addCssParserFunction<Text, &Text::pCssLeading>("leading", this);
	css->addCssParserFunction<Text, &Text::pCssLetterSpacing>("letter-spacing", this);
	css->addCssParserFunction<Text, &Text::pCssWordSpacing>("word-spacing", this);
	css->addCssParserFunction<Text, &Text::pCssTextAlignment>("text-align", this);
}

void Text::onBoxDefinition(BoxDefinition* boxDefinition){
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
	if(value=="justify_all") textAlignment = ALIGN_JUSTIFY_ALL;

}

void Text::onAutoWidth(float& width){
	
}

void Text::onAutoHeight(float& height){
	
}

}

}

