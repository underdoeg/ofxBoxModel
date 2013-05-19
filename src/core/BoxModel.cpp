#include "BoxModel.h"

boxModel::core::BoxModel::BoxModel() {
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

void boxModel::core::BoxModel::recalculate() {
	//get all the values

	float _width = width.getValueCalculated();
	float _height = height.getValueCalculated();

	float _marginLeft = marginLeft.getValueCalculated();
	float _marginRight = marginRight.getValueCalculated();
	float _marginTop = marginTop.getValueCalculated();
	float _marginBottom = marginBottom.getValueCalculated();

	float _paddingLeft = paddingLeft.getValueCalculated();
	float _paddingRight = paddingRight.getValueCalculated();
	float _paddingTop = paddingTop.getValueCalculated();
	float _paddingBottom = paddingBottom.getValueCalculated();

	float _borderLeft = borderLeft.getValueCalculated();
	float _borderRight = borderRight.getValueCalculated();
	float _borderTop = borderTop.getValueCalculated();
	float _borderBottom = borderBottom.getValueCalculated();

	if(width.getType() == Unit::Auto)
		_width = _paddingLeft + _paddingRight + _borderLeft + _borderRight;
	if(height == Unit::Auto)
		_height = _paddingTop + _paddingBottom + _borderTop + _borderBottom;

	size.x = _width;
	outerSize.x = _marginLeft + _marginRight + size.x;
	contentSize.x = size.x - _paddingLeft - _paddingRight - _borderLeft - _borderRight;
	contentPosition.x = _paddingLeft + _borderLeft;

	size.y = _height;
	outerSize.y = _marginTop + _marginBottom + size.y;
	contentSize.y = size.y - _paddingBottom - _paddingTop - _borderTop - _borderBottom;
	contentPosition.y = _paddingTop + _borderTop;

	Event e(this);
	ofNotifyEvent(recalculated, e);
}

void boxModel::core::BoxModel::forcePosition(Point p) {
	forcePosition(p.x, p.y);
}

void boxModel::core::BoxModel::forcePosition(float x, float y) {
	position.x = x;
	position.y = y;
}

void boxModel::core::BoxModel::forceContentSize(float w, float h) {

	float _marginLeft = marginLeft.getValueCalculated();
	float _marginRight = marginRight.getValueCalculated();
	float _marginTop = marginTop.getValueCalculated();
	float _marginBottom = marginBottom.getValueCalculated();

	float _paddingLeft = paddingLeft.getValueCalculated();
	float _paddingRight = paddingRight.getValueCalculated();
	float _paddingTop = paddingTop.getValueCalculated();
	float _paddingBottom = paddingBottom.getValueCalculated();

	float _borderLeft = borderLeft.getValueCalculated();
	float _borderRight = borderRight.getValueCalculated();
	float _borderTop = borderTop.getValueCalculated();
	float _borderBottom = borderBottom.getValueCalculated();

	size.x = w + _paddingLeft + _paddingRight + _borderLeft + _borderRight;;
	size.y = h + _paddingBottom + _paddingTop + _borderTop + _borderBottom;
	outerSize.x = _marginLeft + _marginRight + size.x;
	outerSize.y = _marginTop + _marginBottom + size.y;
	contentSize.x = w;
	contentSize.y = h;
	contentPosition.x = _paddingLeft + _borderLeft;
	contentPosition.y = _paddingTop + _borderTop;


}

void boxModel::core::BoxModel::forceOuterSize(float w, float h) {
	float _marginLeft = marginLeft.getValueCalculated();
	float _marginRight = marginRight.getValueCalculated();
	float _marginTop = marginTop.getValueCalculated();
	float _marginBottom = marginBottom.getValueCalculated();

	float _paddingLeft = paddingLeft.getValueCalculated();
	float _paddingRight = paddingRight.getValueCalculated();
	float _paddingTop = paddingTop.getValueCalculated();
	float _paddingBottom = paddingBottom.getValueCalculated();

	float _borderLeft = borderLeft.getValueCalculated();
	float _borderRight = borderRight.getValueCalculated();
	float _borderTop = borderTop.getValueCalculated();
	float _borderBottom = borderBottom.getValueCalculated();

	size.x = w-_marginLeft-_marginRight;
	size.y = h-_marginTop-_marginBottom;
	outerSize.x = w;
	outerSize.y = h;
	contentSize.x = size.x - _paddingLeft - _paddingRight - _borderLeft - _borderRight;
	contentSize.y = size.y - _paddingBottom - _paddingTop - _borderTop - _borderBottom;
	contentPosition.x = _paddingLeft + _borderLeft;
	contentPosition.y = _paddingTop + _borderTop;
}

void boxModel::core::BoxModel::forceSize(float w, float h) {
	float _marginLeft = marginLeft.getValueCalculated();
	float _marginRight = marginRight.getValueCalculated();
	float _marginTop = marginTop.getValueCalculated();
	float _marginBottom = marginBottom.getValueCalculated();

	float _paddingLeft = paddingLeft.getValueCalculated();
	float _paddingRight = paddingRight.getValueCalculated();
	float _paddingTop = paddingTop.getValueCalculated();
	float _paddingBottom = paddingBottom.getValueCalculated();

	float _borderLeft = borderLeft.getValueCalculated();
	float _borderRight = borderRight.getValueCalculated();
	float _borderTop = borderTop.getValueCalculated();
	float _borderBottom = borderBottom.getValueCalculated();

	size.x = w;
	size.y = h;
	outerSize.x = _marginLeft + _marginRight + size.x;
	outerSize.y = _marginTop + _marginBottom + size.y;
	contentSize.x = size.x - _paddingLeft - _paddingRight - _borderLeft - _borderRight;
	contentSize.y = size.y - _paddingBottom - _paddingTop - _borderTop - _borderBottom;
	contentPosition.x = _paddingLeft + _borderLeft;
	contentPosition.y = _paddingTop + _borderTop;
}
