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
	LISTEN_FOR_COMPONENT(BoxDefinition, Text, onBoxDefinition)
	LISTEN_FOR_COMPONENT(Css, Text, onCss)
}

void Text::onCss(Css* css){
	css->addCssParserFunction<Text, &Text::pCssLeading>("line-height", this);
	css->addCssParserFunction<Text, &Text::pCssLeading>("leading", this);
}

void Text::onBoxDefinition(BoxDefinition* boxDefinition){
	boxDefinition->onHeightAuto.connect<Text, &Text::onAutoHeight>(this);
	boxDefinition->onWidthAuto.connect<Text, &Text::onAutoWidth>(this);
}

void Text::pCssLeading(std::string key, std::string value){
	leading = core::Unit::parseCssNumber(value);
}

void Text::onAutoWidth(float& width){
	
}

void Text::onAutoHeight(float& height){
	
}

}

}

