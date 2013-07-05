#ifndef MARGINBORDERPADDING_H
#define MARGINBORDERPADDING_H

#include "core/Component.h" // Base class: boxModel::core::Component
#include "Box.h"
#include "core/Unit.h"
#include "core/BaseTypes.h"
#include "Css.h"
#include "Stack.h"

namespace boxModel {

namespace components {

enum Position {
    Relative,
    Absolute,
    Fixed
};

enum Floating {
    FloatLeft,
    FloatRight,
    FloatNone
};

class BoxDefinition : public core::Component {
public:
	BoxDefinition();
	~BoxDefinition();
	void setup();
	void recalculateBoxSize();

	core::Unit left;
	core::Unit top;
	core::Unit bottom;
	core::Unit right;

	core::Value<Floating> floating;
	core::Value<Position> positioning;

	core::UnitGroup margin;
	core::UnitGroup padding;
	core::UnitGroup border;

	core::Unit width;
	core::Unit height;

	Nano::signal<void(float&)> onWidthAuto;
	Nano::signal<void(float&)> onHeightAuto;
	
	void onFlush();
	
	static core::Unit parseCssNumber(std::string val);
	static std::vector<core::Unit> parseCssNumberBlock(std::string val);
	static Floating parseCssFloating(std::string val);
	
	void copyFrom(BoxDefinition* boxDefinition);

	
private:
	void pFloat(std::string key, std::string value);
	void pColor(std::string key, std::string value);
	void pBgColor(std::string key, std::string value);
	void pWidth(std::string key, std::string value);
	void pHeight(std::string key, std::string value);
	
	void pPosition(std::string key, std::string value);
	
	void pRight(std::string key, std::string value);
	void pLeft(std::string key, std::string value);
	void pTop(std::string key, std::string value);
	void pBottom(std::string key, std::string value);

	
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

	void onBox(Box* b) {
		box = b;
	}
	
	void onStack(Stack* stack);
	
	void onCss(Css* css);

	void onUnitChanged(core::Unit* u);
	
	void onParentChanged(Stack* s);
	
	void onParentSizeChanged(core::Point p);

	Box* box;
	Stack* stack;
	Box* parentBox;
	
	bool isDirty;
	float autoWidth;
	float autoHeight;
};

}

}

#endif // MARGINBORDERPADDING_H
