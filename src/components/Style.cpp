#include "Style.h"

namespace boxModel {
namespace components {

using namespace core;

std::string Style::getName() {
	return "style";
}

void Style::onCss(Css* css) {
	css->addCssParserFunction<Style, &Style::pCssColor>("color", this);
	css->addCssParserFunction<Style, &Style::pCssBgColor>("background-color", this);
	css->addCssParserFunction<Style, &Style::pCssBorderColor>("border-color", this);
}

void Style::pCssColor(std::string key, std::string value) {
	setColor(parseCssColor(value));
}

void Style::pCssBgColor(std::string key, std::string value) {
	if(value == "none") {
		setBgColorNone();
		return;
	}
	setBgColor(parseCssColor(value));
}

void Style::pCssBorderColor(std::string key, std::string value) {
	setBorderColor(parseCssColor(value));
}

Color Style::parseCssColor(std::string val) {
	int r,g,b,a;
	r = g = b = 0;
	a = 255;
	//convert hex color with #
	if(stringContains(val, "#")) {
		val = stringTrim(stringReplace(val, "#", ""));
		if(val.size() == 2) {
			std::string valNew;
			valNew+=val[0];
			valNew+=val[1];
			valNew+=val[0];
			valNew+=val[1];
			valNew+=val[0];
			valNew+=val[1];
			val = valNew;
		} else if(val.size() == 3) { //check for color short codes
			std::string valNew;
			valNew+=val[0];
			valNew+=val[0];
			valNew+=val[1];
			valNew+=val[1];
			valNew+=val[2];
			valNew+=val[2];
			val = valNew;
		} else if(val.size() == 4) { //check for color short codes
			std::string valNew;
			valNew+=val[0];
			valNew+=val[0];
			valNew+=val[1];
			valNew+=val[1];
			valNew+=val[2];
			valNew+=val[2];
			valNew+=val[3];
			valNew+=val[3];
			val = valNew;
		}
		long int number = (int)strtol(val.c_str(), NULL, 16);
		if(val.size() == 6) {
			r = ((number >> 16) & 0xFF);
			g = ((number >> 8) & 0xFF);
			b = ((number) & 0xFF);
			a = 255;
		} else if(val.size() == 8) {
			r = ((number >> 24) & 0xFF);
			g = ((number >> 16) & 0xFF);
			b = ((number >> 8) & 0xFF);
			a = ((number) & 0xFF);
		}
		return Color(r, g, b, a);
	} else if(stringContains(val, "rgb")) { //for rgb & rgba
		std::vector<std::string> rgbAndNums = stringSplit(val, '(');
		if(rgbAndNums.size()>1) {
			std::vector<std::string> cols = stringSplit(stringReplace(rgbAndNums[1], ")", ""), ',');
			if(cols.size()>0)
				r = stringToInt(cols[0]);
			if(cols.size()>1)
				g = stringToInt(cols[1]);
			if(cols.size()>2)
				b = stringToInt(cols[2]);
			if(cols.size()>3)
				a = stringToInt(cols[3]);
		} else {
			debug::warning("css could not parse color "+val);
		}
	}
	return Color(r, g, b, a);
}

void Style::getInfo(core::Component::Info& info) {

}

void Style::hide() {
	display = DisplayType::NONE;
}

void Style::show() {
	display = DisplayType::BLOCK;
}

void Style::toggle()
{
	if(display == DisplayType::NONE){
		display = DisplayType::BLOCK;
	}else{
		display = DisplayType::NONE;
	}
}

}} // end namespace

