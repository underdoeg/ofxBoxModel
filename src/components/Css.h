#ifndef CSSLOADER_H
#define CSSLOADER_H

#include "Component.h" // Base class: boxModel::core::Component
#include <unordered_map>
#include "Unit.h"
#include "Addressable.h"
#include "Stack.h"
#include <functional>


namespace boxModel {

namespace components {

struct CssProperty {
	CssProperty(std::string k, std::string v) {
		key = k;
		value = v;
	}
	std::string key;
	std::string value;
};

class Css : public boxModel::core::Component {
public:
	Css() {
	}

	~Css() {
	}
	
	std::string getName();
	
	void setup();

	void loadCss(std::string path);
	void setCss(std::string css);
	void setCssBlock(std::string block);
	void applyCssProperty(std::string key, std::string value);
	void applyCssProperty(CssProperty p);
	
	template <typename Type, void(Type::*method)(std::string, std::string)>
	void addCssParserFunction(std::string key, Type* obj){
		addCssParserFunction(key, bind(method, obj, std::placeholders::_1, std::placeholders::_2));
	}
	void addCssParserFunction(std::string key, std::function<void(std::string, std::string)> func);

	/***/

	void copyFrom(Css* css);

protected:
	std::vector<CssProperty> parseCssBlock(std::string propertiesString);
	void applyCss();

private:
	void onSerializer(Serializer* ser);
	void onSerialize(core::VariantList& variants);
	void onDeserialize(core::VariantList& variants);

	void onStack(Stack* stack);
	void onChildAdded(Stack* stack);
	
	std::map<std::string, std::vector<CssProperty> > properties;
	std::vector<std::string> propertiesOrder;
	std::unordered_map<std::string, std::function<void(std::string, std::string)> > parserFunctions;
};


//end namespace
}

}

#endif // CSSLOADER_H
