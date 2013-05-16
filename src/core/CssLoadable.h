#ifndef CSSLOADABLE_H
#define CSSLOADABLE_H

#include "core/BoxModel.h"
#include "debug/Print.h"
#include <slre.h>

namespace ofx {

namespace boxModel {

namespace core {

struct CssProperty {
	CssProperty(std::string k, std::string v) {
		key = k;
		value = v;
	}
	std::string key;
	std::string value;
};

template <class BoxModelType>
class CssLoadable {
public:
	CssLoadable() {};
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
							std::string key = keyAndValue[0];
							std::string value = keyAndValue[1];

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
	}
private:
	//just for internal debugging usage
	void printStringVector(std::vector<std::string> r) {
		for(std::vector<std::string>::iterator it = r.begin(); it<r.end(); it++) {
			std::cout << *it << std::endl << std::endl;
		}
	}

	void printProperties() {

	}

	std::map<std::string, std::vector<CssProperty> > properties;
};

}

}

}

#endif // CSSLOADABLE_H
