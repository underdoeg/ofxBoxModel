#include "Css.h"
#include <fstream>
#include <streambuf>

using namespace boxModel::components;
using namespace boxModel::core;
using namespace std;

void Css::setup() {
}

void Css::loadCss(std::string path) {
	std::ifstream t(path);
	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
	           std::istreambuf_iterator<char>());

	setCss(str);
}

void Css::setCss(std::string cssDefinition) {
	//first remove lin breaks & split for blocks
	cssDefinition = stringRemoveLineBreaks(cssDefinition);

	//remove comments
	std::vector<std::string> commentBlocks = stringSplit(cssDefinition, "*/");
	cssDefinition = "";
	for(std::vector<std::string>::iterator itBlock = commentBlocks.begin(); itBlock<commentBlocks.end(); itBlock++) {
		std::vector<std::string> commentBlocks2 = stringSplit(*itBlock, "/*");
		cssDefinition += commentBlocks2[0];
	}

	//split by blocks
	std::vector<std::string> blocks = stringSplit(cssDefinition, '}');

	//loop all blocks
	for(std::vector<std::string>::iterator itBlock = blocks.begin(); itBlock<blocks.end(); itBlock++) {
		std::string block = stringTrim(*itBlock);
		if(block.size() != 0) {
			std::vector<std::string> addressAndProperties = stringSplit(*itBlock, '{');
			if(addressAndProperties.size() == 2) {

				//now we have the address
				string address = stringTrim(addressAndProperties[0]);
				string propertiesString = addressAndProperties[1];

				std::vector<CssProperty> props = parseCssBlock(propertiesString);
				properties[address].insert(properties[address].end(), props.begin(), props.end());

			} else {
				debug::warning("CSS ERROR near "+addressAndProperties[0]);
			}
		}
	}

	//printProperties();

	applyCss();
}

std::vector<CssProperty> Css::parseCssBlock(std::string propertiesString) {
	std::vector<CssProperty> ret;

	std::vector<std::string> propertyList = stringSplit(propertiesString, ';');

	//now parse all properties
	for(std::vector<std::string>::iterator itProp = propertyList.begin(); itProp<propertyList.end(); itProp++) {
		std::vector<std::string> keyAndValue= stringSplit(*itProp, ':');

		//trim the result
		for(std::vector<std::string>::iterator itKV = keyAndValue.begin(); itKV<keyAndValue.end(); itKV++) {
			*itKV = stringTrim(*itKV);
		}
		if(keyAndValue.size() == 2) {
			std::string key = stringToLower(keyAndValue[0]);
			std::string value = stringToLower(keyAndValue[1]);

			//remove eventual space between number and pixel / %
			value = stringReplace(value, "  ", " ");
			value = stringReplace(value, " px", "px");
			value = stringReplace(value, " %", "%");

			//at this point we have address, key and value, so store it for later use
			ret.push_back(CssProperty(key, value));
		} else {
			debug::warning("CSS ERROR near "+keyAndValue[0]);
		}
	}
	return ret;
}

void Css::setCssBlock(std::string block) {
	std::vector<CssProperty> props = parseCssBlock(block);
	for(CssProperty& prop: props) {
		applyCssProperty(prop);
	}
}

void Css::applyCssProperty(std::string key, std::string value) {
	applyCssProperty(CssProperty(key, value));
}

void Css::applyCssProperty(CssProperty p) {
	if (parserFunctions.find(p.key) == parserFunctions.end() ) {
		debug::warning("CSS unknown property: "+p.key);
		return;
	}
	parserFunctions[p.key](p.key, p.value);
}


void Css::applyCss() {
	if(!components->hasComponent<Addressable>()) {
		debug::warning("Css needs Addressable to apply properties");
		return;
	}
	//apply CSS style to self and children found by addresses stored in the property list
	for(auto props: properties) {
		std::vector<Addressable*> addressables = components->getComponent<Addressable>()->findByAddress(props.first);
		for(Addressable* addressable: addressables) {
			if(addressable->components->hasComponent<Css>()) {
				Css* cssChild = addressable->components->getComponent<Css>();
				for(CssProperty& prop: props.second) {
					cssChild->applyCssProperty(prop);
				}
			}
		}
	}
}

void Css::addCssParserFunction(std::string key, std::function<void(std::string, std::string)> func) {
	parserFunctions[key] = func;
}

/*
Color Css::parseColor(std::string val) {
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
*/