#ifndef CSSLOADER_H
#define CSSLOADER_H

#include "Component.h" // Base class: boxModel::core::Component
#include <unordered_map>
#include "Unit.h"
#include "BoxDefinition.h"
#include "Addressable.h"
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
	Css():boxDefinition(NULL) {
	}

	~Css() {
	}

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
	static core::Unit parseCssNumber(std::string val);
	static std::vector<core::Unit> parseCssNumberBlock(std::string val);
	static Floating parseCssFloating(std::string val);
	static core::Color parseColor(std::string val);

protected:
	std::vector<CssProperty> parseCssBlock(std::string propertiesString);
	void applyCss();

private:
	void onBoxDefinition(BoxDefinition* boxDef);
	void pFloat(std::string key, std::string value);
	void pColor(std::string key, std::string value);
	void pBgColor(std::string key, std::string value);
	void pWidth(std::string key, std::string value);
	void pHeight(std::string key, std::string value);
	
	/* MARGIN, PADDING, BORDER */
	void pMargin(std::string key, std::string value);
	void pMarginLeft(std::string key, std::string value);
	void pMarginRight(std::string key, std::string value);
	void pMarginTop(std::string key, std::string value);
	void pMarginBottom(std::string key, std::string value);
	
	void pPadding(std::string key, std::string value);
	void pPaddingLeft(std::string key, std::string value);
	void pPaddingRight(std::string key, std::string value);
	void pPaddingTop(std::string key, std::string value);
	void pPaddingBottom(std::string key, std::string value);
	
	void pBorder(std::string key, std::string value);
	void pBorderLeft(std::string key, std::string value);
	void pBorderRight(std::string key, std::string value);
	void pBorderTop(std::string key, std::string value);
	void pBorderBottom(std::string key, std::string value);

	std::unordered_map<std::string, std::vector<CssProperty> > properties;
	std::unordered_map<std::string, std::function<void(std::string, std::string)> > parserFunctions;
	BoxDefinition* boxDefinition;
};


//end namespace
}

}

#endif // CSSLOADER_H
