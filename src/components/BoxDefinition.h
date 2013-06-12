#ifndef MARGINBORDERPADDING_H
#define MARGINBORDERPADDING_H

#include "core/Component.h" // Base class: boxModel::core::Component
#include "Box.h"
#include "core/Unit.h"
#include "core/BaseTypes.h"
#include "Css.h"

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
	BoxDefinition() {
		floating = FloatNone;
		positioning = Relative;
		border = core::Unit::Type_None;
	}
	~BoxDefinition() {
	}

	void setup() {
		box = NULL;
		LISTEN_FOR_COMPONENT(Box, BoxDefinition, onBox)
		LISTEN_FOR_COMPONENT(Css, BoxDefinition, onCss)

		margin.unitChanged.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
		padding.unitChanged.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
		border.unitChanged.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);

		width.changed.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
		height.changed.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);

		
	}

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
	
	static core::Unit parseCssNumber(std::string val);
	static std::vector<core::Unit> parseCssNumberBlock(std::string val);
	static Floating parseCssFloating(std::string val);
	
	void recalculateBoxSize() {
		if(box == NULL)
			return;

		float _width = width.getValueCalculated();
		float _height = height.getValueCalculated();

		float _marginLeft = margin.left.getValueCalculated();
		float _marginRight = margin.right.getValueCalculated();
		float _marginTop = margin.top.getValueCalculated();
		float _marginBottom = margin.bottom.getValueCalculated();

		float _paddingLeft = padding.left.getValueCalculated();
		float _paddingRight = padding.right.getValueCalculated();
		float _paddingTop = padding.top.getValueCalculated();
		float _paddingBottom = padding.bottom.getValueCalculated();

		float _borderLeft = border.left.getValueCalculated();
		float _borderRight = border.right.getValueCalculated();
		float _borderTop = border.top.getValueCalculated();
		float _borderBottom = border.bottom.getValueCalculated();

		if(width.getType() == core::Unit::Auto) {
			onWidthAuto(_width);
			_width += _paddingLeft + _paddingRight + _borderLeft + _borderRight;
		}
		if(height.getType() == core::Unit::Auto) {
			onHeightAuto(_height);
			_height += _paddingTop + _paddingBottom + _borderTop + _borderBottom;
		}
				
		box->size.x = _width;
		box->outerSize.x = _marginLeft + _marginRight + box->size.x;
		box->contentSize.x = box->size.x - _paddingLeft - _paddingRight - _borderLeft - _borderRight;
		box->contentPosition.x = _paddingLeft + _borderLeft;

		box->size.y = _height;
		box->outerSize.y = _marginTop + _marginBottom + box->size.y;
		box->contentSize.y = box->size.y - _paddingBottom - _paddingTop - _borderTop - _borderBottom;
		box->contentPosition.y = _paddingTop + _borderTop;
	}

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
	
	void onCss(Css* css);

	void onUnitChanged(core::Unit* u) {
		recalculateBoxSize();
	}

	Box* box;
};

}

}

#endif // MARGINBORDERPADDING_H
