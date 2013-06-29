#include "BoxDefinition.h"

using namespace boxModel::components;
using namespace boxModel::core;


BoxDefinition::BoxDefinition() {
	floating = FloatNone;
	positioning = Relative;
	border = core::Unit::Type_None;
	height = core::Unit::Auto;
	width = core::Unit::Percent;
	width = 100;
	stack = NULL;
	parentBox = NULL;
	autoWidth = 0;
	autoHeight = 0;
}
BoxDefinition::~BoxDefinition() {
}

void BoxDefinition::setup() {
	isDirty = false;
	box = NULL;
	LISTEN_FOR_COMPONENT(Box, BoxDefinition, onBox)
	LISTEN_FOR_COMPONENT(Css, BoxDefinition, onCss)
	LISTEN_FOR_COMPONENT(Stack, BoxDefinition, onStack)

	margin.unitChanged.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
	padding.unitChanged.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
	border.unitChanged.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);

	width.changed.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);
	height.changed.connect<BoxDefinition, &BoxDefinition::onUnitChanged>(this);

	components->addUnitX(&width);
	components->addUnitGroup(&margin);
	components->addUnitGroup(&padding);
	components->addUnitGroup(&border);
	components->addUnitY(&height);
}

void BoxDefinition::onStack(Stack* s)
{
	stack = s;
	stack->parentChanged.connect<BoxDefinition, &BoxDefinition::onParentChanged>(this);
}

void BoxDefinition::onParentChanged(Stack* parent)
{
	if(parent == NULL)
		return;
	if(parentBox != NULL)
		parentBox->contentSize.changed.disconnect<BoxDefinition, &BoxDefinition::onParentSizeChanged>(this);
	recalculateBoxSize();
	if(parent->components->hasComponent<Box>()){
		parentBox = parent->components->getComponent<Box>();
		parentBox->contentSize.changed.connect<BoxDefinition, &BoxDefinition::onParentSizeChanged>(this);
	}
}

void BoxDefinition::onParentSizeChanged(core::Point p)
{
	//recalculateBoxSize();
}

void BoxDefinition::onUnitChanged(core::Unit* u) {
	recalculateBoxSize();
}

void BoxDefinition::recalculateBoxSize() {
	isDirty = true;
	if(!isDirty)
		return;
		
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
		_width = autoWidth;
		_width += _paddingLeft + _paddingRight + _borderLeft + _borderRight;
	}
	
	box->size.x = _width;
	box->outerSize.x = _marginLeft + _marginRight + box->size.x;
	box->contentSize.x = box->size.x - _paddingLeft - _paddingRight - _borderLeft - _borderRight;
	box->contentPosition.x = _paddingLeft + _borderLeft;

	if(height.getType() == core::Unit::Auto) {
		_height = autoHeight;
		_height += _paddingTop + _paddingBottom + _borderTop + _borderBottom;
	}

	box->size.y = _height;
	box->outerSize.y = _marginTop + _marginBottom + box->size.y;
	box->contentSize.y = box->size.y - _paddingBottom - _paddingTop - _borderTop - _borderBottom;
	box->contentPosition.y = _paddingTop + _borderTop;
}

void boxModel::components::BoxDefinition::onFlush()
{
	if(width.getType() == core::Unit::Auto) {
		onWidthAuto(autoWidth);
	}
	
	if(height.getType() == core::Unit::Auto) {
		onHeightAuto(autoHeight);
	}
	recalculateBoxSize();
}

/************************ PARSER FUNCTIONS *******************************/

void BoxDefinition::onCss(Css* css) {
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pFloat>("float", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pWidth>("width", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pHeight>("height", this);

	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pPosition>("position", this);

	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pTop>("top", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pLeft>("left", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pRight>("right", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pBottom>("bottom", this);

	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pMargin>("margin", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pMarginLeft>("margin-left", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pMarginRight>("margin-right", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pMarginBottom>("margin-bottom", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pMarginTop>("margin-top", this);

	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pPadding>("padding", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pPaddingLeft>("padding-left", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pPaddingRight>("padding-right", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pPaddingBottom>("padding-bottom", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pPaddingTop>("padding-top", this);

	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pBorder>("border", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pBorderLeft>("border-left", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pBorderRight>("border-right", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pBorderBottom>("border-bottom", this);
	css->addCssParserFunction<BoxDefinition, &BoxDefinition::pBorderTop>("border-top", this);
}

/************************ PARSER HELPERS *******************************/

Floating BoxDefinition::parseCssFloating(std::string val) {
	if(val == "left")
		return FloatLeft;
	if(val == "right")
		return FloatLeft;
	return FloatNone;
}

/******************************************** CSS LISTENERS **************************************************/

void BoxDefinition::pHeight(std::string key, std::string value) {
	height = Unit::parseCssNumber(value);
}

void BoxDefinition::pWidth(std::string key, std::string value) {
	width = Unit::parseCssNumber(value);
}

void BoxDefinition::pTop(std::string key, std::string value) {
	top = Unit::parseCssNumber(value);
}

void BoxDefinition::pRight(std::string key, std::string value) {
	right = Unit::parseCssNumber(value);
}

void BoxDefinition::pLeft(std::string key, std::string value) {
	left = Unit::parseCssNumber(value);
}

void BoxDefinition::pBottom(std::string key, std::string value) {
	bottom = Unit::parseCssNumber(value);
}

void BoxDefinition::pPosition(std::string key, std::string value) {
	if(value == "absolute")
		positioning = Absolute;
	if(value == "relative")
		positioning = Relative;
	if(value == "fixed")
		positioning = Fixed;
}

void BoxDefinition::pFloat(std::string key, std::string value) {
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

void BoxDefinition::pMargin(std::string key, std::string value) {
	parseUnitGroup(&margin, value);
}
void BoxDefinition::pMarginLeft(std::string key, std::string value) {
	margin.left = Unit::parseCssNumber(value);
}
void BoxDefinition::pMarginRight(std::string key, std::string value) {
	margin.right = Unit::parseCssNumber(value);
}
void BoxDefinition::pMarginTop(std::string key, std::string value) {
	margin.top = Unit::parseCssNumber(value);
}
void BoxDefinition::pMarginBottom(std::string key, std::string value) {
	margin.bottom = Unit::parseCssNumber(value);
}
//////////////////////////////////////////////////////////////////
void BoxDefinition::pPadding(std::string key, std::string value) {
	parseUnitGroup(&padding, value);
}
void BoxDefinition::pPaddingLeft(std::string key, std::string value) {
	padding.left = Unit::parseCssNumber(value);
}
void BoxDefinition::pPaddingRight(std::string key, std::string value) {
	padding.right = Unit::parseCssNumber(value);
}
void BoxDefinition::pPaddingTop(std::string key, std::string value) {
	padding.top = Unit::parseCssNumber(value);
}
void BoxDefinition::pPaddingBottom(std::string key, std::string value) {
	padding.bottom = Unit::parseCssNumber(value);
}
//////////////////////////////////////////////////////////////////
void BoxDefinition::pBorder(std::string key, std::string value) {
	parseUnitGroup(&border, value);
}
void BoxDefinition::pBorderLeft(std::string key, std::string value) {
	border.left = Unit::parseCssNumber(value);
}
void BoxDefinition::pBorderRight(std::string key, std::string value) {
	border.right = Unit::parseCssNumber(value);
}
void BoxDefinition::pBorderTop(std::string key, std::string value) {
	border.top = Unit::parseCssNumber(value);
}
void BoxDefinition::pBorderBottom(std::string key, std::string value) {
	border.bottom = Unit::parseCssNumber(value);
}
