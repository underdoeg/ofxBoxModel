#include "BoxModel.h"

ofx::boxModel::core::BoxModel::BoxModel()
{
	padding.add(&paddingLeft);
	padding.add(&paddingRight);
	padding.add(&paddingTop);
	padding.add(&paddingBottom);
	ofAddListener(padding.changed, this, &BoxModel::unitChanged);

	margin.add(&marginLeft);
	margin.add(&marginRight);
	margin.add(&marginTop);
	margin.add(&marginBottom);
	ofAddListener(margin.changed, this, &BoxModel::unitChanged);

	border.add(&borderLeft);
	border.add(&borderRight);
	border.add(&borderTop);
	border.add(&borderBottom);
	ofAddListener(border.changed, this, &BoxModel::unitChanged);

	ofAddListener(width.changed, this, &BoxModel::unitChanged);
	ofAddListener(height.changed, this, &BoxModel::unitChanged);

	positioning = Relative;
	floating = FloatNone;
	clearing = false;

	properties.push_back(&positioning);
	properties.push_back(&floating);
	properties.push_back(&clearing);

	for(std::vector<PropertyBase*>::iterator it = properties.begin(); it!=properties.end(); it++) {
		ofAddListener((*it)->changed, this, &BoxModel::propertyChanged);
	}
}

void ofx::boxModel::core::BoxModel::recalculate()
{
	//get all the values
	float _width = width.getValueCalculated(containerSize.x);
	float _height = height.getValueCalculated(containerSize.y);

	float _marginLeft = marginLeft.getValueCalculated(containerSize.x);
	float _marginRight = marginRight.getValueCalculated(containerSize.x);
	float _marginTop = marginTop.getValueCalculated(containerSize.y);
	float _marginBottom = marginBottom.getValueCalculated(containerSize.y);

	float _paddingLeft = paddingLeft.getValueCalculated(containerSize.x);
	float _paddingRight = paddingRight.getValueCalculated(containerSize.x);
	float _paddingTop = paddingTop.getValueCalculated(containerSize.y);
	float _paddingBottom = paddingBottom.getValueCalculated(containerSize.y);

	float _borderLeft = borderLeft.getValueCalculated(containerSize.x);
	float _borderRight = borderRight.getValueCalculated(containerSize.x);
	float _borderTop = borderTop.getValueCalculated(containerSize.y);
	float _borderBottom = borderBottom.getValueCalculated(containerSize.y);

	size.x = _width;
	size.y = _height;
	outerSize.x = _marginLeft + _marginRight + size.x;
	outerSize.y = _marginTop + _marginBottom + size.y;
	contentSize.x = size.x - _paddingLeft - _paddingRight - _borderLeft - _borderRight;
	contentSize.y = size.y - _paddingBottom - _paddingTop - _borderTop - _borderBottom;
	contentPosition.x = _paddingLeft + _borderLeft;
	contentPosition.y = _paddingTop + _borderTop;
}

