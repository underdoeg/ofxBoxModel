#ifndef MARGINBORDERPADDING_H
#define MARGINBORDERPADDING_H

#include "Component.h" // Base class: boxModel::core::Component
#include "Unit.h"

namespace boxModel {

namespace components {

class BoxDefinition : public core::Component {
public:
	BoxDefinition() {
	}
	~BoxDefinition() {
	}

	void setup() {
		margin.unitChanged.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
		padding.unitChanged.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
		border.unitChanged.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
		
		width.changed.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
		height.changed.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
	}

	core::UnitGroup margin;
	core::UnitGroup padding;
	core::UnitGroup border;

	core::Unit width;
	core::Unit height;

private:
	void onUnitChanged(core::Unit* u){
		recalculate();
	}

	void recalculate(){
		if(!components->hasComponent<Box>())
			return;
		
		Box* box = components->getComponent<Box>();
		
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

		if(width.getType() == core::Unit::Auto)
			_width = _paddingLeft + _paddingRight + _borderLeft + _borderRight;
		if(height == core::Unit::Auto)
			_height = _paddingTop + _paddingBottom + _borderTop + _borderBottom;

		box->size.x = _width;
		box->outerSize.x = _marginLeft + _marginRight + box->size.x;
		box->contentSize.x = box->size.x - _paddingLeft - _paddingRight - _borderLeft - _borderRight;
		box->contentPosition.x = _paddingLeft + _borderLeft;

		box->size.y = _height;
		box->outerSize.y = _marginTop + _marginBottom + box->size.y;
		box->contentSize.y = box->size.y - _paddingBottom - _paddingTop - _borderTop - _borderBottom;
		box->contentPosition.y = _paddingTop + _borderTop;
	}
};

}

}

#endif // MARGINBORDERPADDING_H
