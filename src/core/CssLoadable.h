#ifndef CSSLOADABLE_H
#define CSSLOADABLE_H

#include "core/BoxModel.h"
#include "debug/Print.h"
#include <slre.h>

namespace ofx {

namespace boxModel {

namespace core {

/***********************************************************************************************/


struct CssProperty {
	CssProperty(std::string k, std::string v) {
		key = k;
		value = v;
	}
	std::string key;
	std::string value;
};

class CssPropertyParserPtrBase {
public:
	virtual void call(std::string, std::string) = 0;
};

template <typename T>
class CssPropertyParserPtr : public CssPropertyParserPtrBase {
public:
	CssPropertyParserPtr(T* who, void (T::*memfunc)(std::string, std::string))
		: pt2Member(memfunc), inst(who) {
	}
	void call(std::string s, std::string k) {
		(inst->*pt2Member)(s, k);
	}
private:
	void (T::*pt2Member)(std::string, std::string);
	T *inst;
};

template <typename T>
CssPropertyParserPtrBase * makeCssPropertyParserPtr(T* who, void (T::*memfunc)(std::string, std::string)) {
	return new CssPropertyParserPtr<T>(who, memfunc);
}

/***********************************************************************************************/

template <class BoxModelType>
class CssLoadable {
public:
	typedef std::map<std::string, std::vector<CssProperty> > PropertyList;
	typedef std::map<std::string, CssPropertyParserPtrBase*> PropertyParserList;

	CssLoadable() {
		registerParsers();
	};
	~CssLoadable() {};

	void loadCss(std::string path) {
		ofBuffer buffer = ofBufferFromFile(path);
		setCss(buffer.getText());
	}

	void setCss(std::string cssDefinition) {
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

							//at this point we have address, key and value, so store it for later use
							CssProperty p(key, value);
							/*if(properties.find(address) == properties.end()){
								properties[address] = std::vector<CssProperty>();
							}*/
							properties[address].push_back(p);
						} else {
							debug::warning("CSS ERROR near "+address+" -> "+keyAndValue[0]);
						}
					}
				} else {
					debug::warning("CSS ERROR near "+addressAndProperties[0]);
				}
			}
		}

		printProperties();

		applyCss();
	}

	void registerCssPropertyParser(std::string property, CssPropertyParserPtrBase* func) {
		propertyParsers[stringToLower(property)] = func;
	}

	void applyCssProperty(std::string key, std::string value) {
		applyCssProperty(CssProperty(key, value));
	}

	void applyCssProperty(CssProperty p) {
		if (propertyParsers.find(p.key) == propertyParsers.end() ) {
			debug::warning("CSS unknown key: "+p.key);
			return;
		}
		propertyParsers[p.key]->call(p.key, p.value);
	}

protected:
	Unit parseCssNumber(std::string val) {
		Unit u;
		std::string num = "";
		if(val.rfind("%") != std::string::npos){
			u = Unit::Pixel;
			num = stringTrim(stringReplace(val, "%", ""));
		}else if(val.rfind("px") != std::string::npos){
			u = Unit::Pixel;
			num = stringTrim(stringReplace(val, "px", ""));
		}else{
			u = Unit::Pixel;
			num = val;
		}
		u = stringToFloat(num);
		return u;
	}

	void applyCss() {
		//apply CSS style to self and children found by addresses stored in the property list
		BoxModelType* instance = crtpSelfPtr<CssLoadable, BoxModelType>(this);
		for(PropertyList::iterator it = properties.begin(); it != properties.end(); it++) {
			std::vector<BoxModelType*> boxes = instance->findByAddress(it->first);
			for(typename std::vector<BoxModelType*>::iterator itBoxes = boxes.begin(); itBoxes < boxes.end(); itBoxes++) {
				for(std::vector<CssProperty>::iterator itProps = it->second.begin(); itProps < it->second.end(); itProps++) {
					(*itBoxes)->applyCssProperty(*itProps);
				}
			}
		}
	}

	void registerParsers() {
#define REGISTER_PARSER(NAME, FUNCTION) registerCssPropertyParser(NAME, makeCssPropertyParserPtr<CssLoadable<BoxModelType> >(this, &CssLoadable<BoxModelType>::FUNCTION));
		REGISTER_PARSER("margin", pMargin)
		REGISTER_PARSER("padding", pPadding)
#undef REGISTER_PARSER
	}

	void pMargin(std::string key, std::string value) {
		BoxModelType* instance = crtpSelfPtr<CssLoadable, BoxModelType>(this);
		instance->margin = parseCssNumber(value);
	}

	void pPadding(std::string key, std::string value) {
		BoxModelType* instance = crtpSelfPtr<CssLoadable, BoxModelType>(this);
		instance->padding = parseCssNumber(value);
	}

private:
	//just for internal debugging usage
	void printStringVector(std::vector<std::string> r) {
		for(std::vector<std::string>::iterator it = r.begin(); it<r.end(); it++) {
			std::cout << *it << std::endl << std::endl;
		}
	}

	void printProperties() {
		std::string logString;
		for(PropertyList::iterator it = properties.begin(); it != properties.end(); it++) {
			logString += "\n\n"+it->first + "\n==============\n";
			for(std::vector<CssProperty>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
				logString += (*it2).key+": "+(*it2).value;
				if(it2 != it->second.end()-1)
					logString += "\n";
			}
		}
		debug::notice(logString);
	}

	PropertyList properties;
	PropertyParserList propertyParsers;
};

}

}

}

#endif // CSSLOADABLE_H
