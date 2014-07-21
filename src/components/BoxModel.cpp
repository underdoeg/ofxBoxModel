#include "Box.h"

using namespace boxModel::components;
using namespace boxModel::core;


BoxModel::BoxModel() {
	floating = FloatNone;
	positioning = Relative;
	border = core::Unit::Type_None;
	height = core::Unit::Auto;
	width = core::Unit::Percent;
	align = AlignNone;
	valign = AlignNone;
	width = 100;
	stack = NULL;
	parentBox = NULL;
	autoWidth = 0;
	autoHeight = 0;
	doBoxDefinitionUpdate = true;
}

BoxModel::~BoxModel() {

}

std::string BoxModel::getName() {
	return "box definition";
}

void BoxModel::setup() {
	isDirty = false;
	box = NULL;
	
	autoWidth = 0;
	autoHeight = 0;
	
	LISTEN_FOR_COMPONENT(BoxDefinition, BoxModel, onBox)
	LISTEN_FOR_COMPONENT(Css, BoxModel, onCss)
	LISTEN_FOR_COMPONENT(Stack, BoxModel, onStack)

	margin.unitChanged.connect<BoxModel, &BoxModel::onUnitChanged>(this);
	padding.unitChanged.connect<BoxModel, &BoxModel::onUnitChanged>(this);
	border.unitChanged.connect<BoxModel, &BoxModel::onUnitChanged>(this);

	width.changed.connect<BoxModel, &BoxModel::onUnitChanged>(this);
	height.changed.connect<BoxModel, &BoxModel::onUnitChanged>(this);

	components->addUnitX(&width);
	components->addUnitGroup(&margin);
	components->addUnitGroup(&padding);
	components->addUnitGroup(&border);
	components->addUnitY(&height);
	components->addUnitX(&left);
	components->addUnitX(&right);
	components->addUnitY(&top);
	components->addUnitY(&bottom);
}

void BoxModel::copyFrom(BoxModel* bd) {
	margin = bd->margin;
	padding = bd->padding;
	border = bd->border;
	width = bd->width;
	height = bd->height;
}

void BoxModel::onStack(Stack* s) {
	stack = s;
	stack->parentChanged.connect<BoxModel, &BoxModel::onParentChanged>(this);
}

void BoxModel::onParentChanged(Stack* parent) {
	if(parent == NULL)
		return;
	if(parentBox != NULL){
		parentBox->contentSize.changed.disconnect<BoxModel, &BoxModel::onParentSizeChanged>(this);
	}
	parentBox = NULL;
	parentBoxModel = NULL;
	
	recalculateBoxSize();
	if(parent->components->hasComponent<BoxDefinition>()) {
		parentBox = parent->components->getComponent<BoxDefinition>();
		parentBox->contentSize.changed.connect<BoxModel, &BoxModel::onParentSizeChanged>(this);
	}
	if(parent->components->hasComponent<BoxModel>()) {
		parentBoxModel = parent->components->getComponent<BoxModel>();
	}
}

void BoxModel::onParentSizeChanged(core::Point p) {
	//recalculateBoxSize();
}

void BoxModel::onUnitChanged(core::Unit* u) {
	recalculateBoxSize();
}

void BoxModel::setBoxDefinitionUpdate(bool state) {
	doBoxDefinitionUpdate = state;
}

void BoxModel::recalculateBoxSize() {
	if(!doBoxDefinitionUpdate)
		return;
	isDirty = true;
	if(!isDirty)
		return;

	if(box == NULL)
		return;

	//cout << "RECALCULATE " << endl;
	//components->logInfo();

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
		_width = autoWidth;
		_width += _paddingLeft + _paddingRight + _borderLeft + _borderRight;
	} else if(width.getType() == core::Unit::Percent) {
		_width -= _marginLeft;
		_width -= _marginRight;
	}

	if(minWidth.isSet()) {
		float _minWidth = minWidth.getValueCalculated();
		if(_width < _minWidth)
			_width = _minWidth;
	}

	if(minHeight.isSet()) {
		float _minHeight = minHeight.getValueCalculated();
		if(_height < _minHeight)
			_height = _minHeight;
	}

	//store them first, before triggering potential listeners
	float outerX = _marginLeft + _marginRight + box->size.x;
	
	//if(parentBoxModel && parentBoxModel.)
	
	box->size.x = _width;
	box->outerSize.x = outerX;
	box->contentSize.x = box->size.x - _paddingLeft - _paddingRight - _borderLeft - _borderRight;
	box->contentPosition.x = _paddingLeft + _borderLeft;

	if(height.getType() == core::Unit::Auto) {
		_height = autoHeight;
		_height += _paddingTop + _paddingBottom + _borderTop + _borderBottom;
	} else if(height.getType() == core::Unit::Percent) {
		_height -= _marginTop;
		_height -= _marginBottom;
	}

	box->size.y = _height;
	box->outerSize.y = _marginTop + _marginBottom + box->size.y;
	box->contentSize.y = box->size.y - _paddingBottom - _paddingTop - _borderTop - _borderBottom;
	box->contentPosition.y = _paddingTop + _borderTop;
	
	//check if the parent has too small of an auto width stored
	
	/*
	if(positioning == Position::Absolute){

	}
	*/
}

void boxModel::components::BoxModel::getWidthAuto(float& widthAuto) {
	if(width.getType() != core::Unit::Auto)
		return;
	
	onWidthAuto(widthAuto);
	/*
	if(stack) {
		for(BoxModel* childBox: stack->getChildrenComponents<BoxModel>()) {
			childBox->getWidthAuto(widthAuto);
		}
	}
	*/
}

void boxModel::components::BoxModel::getHeightAuto(float& heightAuto) {
	if(height.getType() != core::Unit::Auto)
		return;
	onHeightAuto(heightAuto);
	/*
	if(stack) {
		for(BoxModel* childBox: stack->getChildrenComponents<BoxModel>()) {
			childBox->getHeightAuto(heightAuto);
		}
	}
	*/
}

void boxModel::components::BoxModel::onFlush() {

	autoWidth = 0;
	getWidthAuto(autoWidth);
	
	autoHeight = 0;
	getHeightAuto(autoHeight);

	if(width.getType() == core::Unit::Auto || height.getType() == core::Unit::Auto)
		recalculateBoxSize();
}

/************************ PARSER FUNCTIONS *******************************/

void BoxModel::onCss(Css* css) {
	css->addCssParserFunction<BoxModel, &BoxModel::pFloat>("float", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pWidth>("width", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pHeight>("height", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pMinWidth>("min-width", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pMinHeight>("min-height", this);

	css->addCssParserFunction<BoxModel, &BoxModel::pPosition>("position", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pAlign>("align", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pVAlign>("valign", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pVAlign>("vertical-align", this);

	css->addCssParserFunction<BoxModel, &BoxModel::pTop>("top", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pLeft>("left", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pRight>("right", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pBottom>("bottom", this);

	css->addCssParserFunction<BoxModel, &BoxModel::pMargin>("margin", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pMarginLeft>("margin-left", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pMarginRight>("margin-right", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pMarginBottom>("margin-bottom", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pMarginTop>("margin-top", this);

	css->addCssParserFunction<BoxModel, &BoxModel::pPadding>("padding", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pPaddingLeft>("padding-left", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pPaddingRight>("padding-right", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pPaddingBottom>("padding-bottom", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pPaddingTop>("padding-top", this);

	css->addCssParserFunction<BoxModel, &BoxModel::pBorder>("border-width", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pBorderLeft>("border-left-width", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pBorderRight>("border-right-width", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pBorderBottom>("border-bottom-width", this);
	css->addCssParserFunction<BoxModel, &BoxModel::pBorderTop>("border-top-width", this);
}

/************************ PARSER HELPERS *******************************/

Floating BoxModel::parseCssFloating(std::string val) {
	if(val == "left")
		return FloatLeft;
	if(val == "right")
		return FloatLeft;
	return FloatNone;
}

/******************************************** CSS LISTENERS **************************************************/

void BoxModel::pHeight(std::string key, std::string value) {
	height = Unit::parseCssNumber(value);
}

void BoxModel::pWidth(std::string key, std::string value) {
	width = Unit::parseCssNumber(value);
}

void BoxModel::pMinHeight(std::string key, std::string value) {
	minHeight = Unit::parseCssNumber(value);
}

void BoxModel::pMinWidth(std::string key, std::string value) {
	minWidth = Unit::parseCssNumber(value);
}

void BoxModel::pTop(std::string key, std::string value) {
	top = Unit::parseCssNumber(value);
}

void BoxModel::pRight(std::string key, std::string value) {
	right = Unit::parseCssNumber(value);
}

void BoxModel::pLeft(std::string key, std::string value) {
	left = Unit::parseCssNumber(value);
}

void BoxModel::pBottom(std::string key, std::string value) {
	bottom = Unit::parseCssNumber(value);
}

void BoxModel::pPosition(std::string key, std::string value) {
	if(value == "absolute")
		positioning = Absolute;
	if(value == "relative")
		positioning = Relative;
	if(value == "fixed")
		positioning = Fixed;
}

void BoxModel::pAlign(std::string key, std::string value) {
	if(value == "none")
		align = AlignNone;
	if(value == "left")
		align = Left;
	else if(value == "right")
		align = Right;
	else if(value == "middle" || value == "center")
		align = Middle;
}

void BoxModel::pVAlign(std::string key, std::string value) {
	if(value == "none")
		valign = AlignNone;
	if(value == "top")
		valign = Top;
	else if(value == "bottom")
		valign = Bottom;
	else if(value == "middle" || value == "center")
		valign = Middle;
}

void BoxModel::pFloat(std::string key, std::string value) {
	floating = parseCssFloating(value);
}

void parseUnitGroup(UnitGroup* u, std::string value) {
	std::vector<Unit> units = Unit::parseCssNumberBlock(value);
	if(units.size() == 1)
		u->set(units[0]);
	else if(units.size() == 2) {
		u->top = units[0];
		u->bottom = units[0];
		u->left = units[1];
		u->right = units[1];
	} else if(units.size() == 3) {
		u->top = units[0];
		u->right = units[1];
		u->bottom = units[2];
	} else if(units.size() >= 4) {
		u->top = units[0];
		u->right = units[1];
		u->bottom = units[2];
		u->left = units[3];
	}
}

void BoxModel::pMargin(std::string key, std::string value) {
	parseUnitGroup(&margin, value);
}
void BoxModel::pMarginLeft(std::string key, std::string value) {
	margin.left = Unit::parseCssNumber(value);
}
void BoxModel::pMarginRight(std::string key, std::string value) {
	margin.right = Unit::parseCssNumber(value);
}
void BoxModel::pMarginTop(std::string key, std::string value) {
	margin.top = Unit::parseCssNumber(value);
}
void BoxModel::pMarginBottom(std::string key, std::string value) {
	margin.bottom = Unit::parseCssNumber(value);
}
//////////////////////////////////////////////////////////////////
void BoxModel::pPadding(std::string key, std::string value) {
	parseUnitGroup(&padding, value);
}
void BoxModel::pPaddingLeft(std::string key, std::string value) {
	padding.left = Unit::parseCssNumber(value);
}
void BoxModel::pPaddingRight(std::string key, std::string value) {
	padding.right = Unit::parseCssNumber(value);
}
void BoxModel::pPaddingTop(std::string key, std::string value) {
	padding.top = Unit::parseCssNumber(value);
}
void BoxModel::pPaddingBottom(std::string key, std::string value) {
	padding.bottom = Unit::parseCssNumber(value);
}
//////////////////////////////////////////////////////////////////
void BoxModel::pBorder(std::string key, std::string value) {
	parseUnitGroup(&border, value);
}
void BoxModel::pBorderLeft(std::string key, std::string value) {
	border.left = Unit::parseCssNumber(value);
}
void BoxModel::pBorderRight(std::string key, std::string value) {
	border.right = Unit::parseCssNumber(value);
}
void BoxModel::pBorderTop(std::string key, std::string value) {
	border.top = Unit::parseCssNumber(value);
}
void BoxModel::pBorderBottom(std::string key, std::string value) {
	border.bottom = Unit::parseCssNumber(value);
}

void BoxModel::getInfo(core::Component::Info& info) {
	
}
