#include "Box.h"


namespace ofx
{
namespace BoxModel
{

Box::Box():bParent(false)
{
	ofAddListener(definition.changed, this, &Box::definitionChanged);
}

Box::~Box()
{
}

void Box::setParent(Box* box)
{
	bParent = true;
	parent = box;
}


void Box::add(Box* box)
{
	box->setParent(this);
	children.push_back(box);
}

Box* Box::createChild()
{
	Box* ret = new Box();
	add(ret);
	return ret;
}

void Box::debugDraw()
{
	ofPushStyle();
	ofFill();
	ofSetColor(200);
	ofRect(position, size.x, size.y);
	ofNoFill();
	ofSetColor(70);
	ofRect(position, size.x, size.y);

	ofLine(position + contentPosition, position + contentPosition + contentSize);
	ofLine(position + contentPosition + Point(contentSize.x, 0), position + contentPosition + Point(0, contentSize.y));
	ofPopStyle();
	
	for(List::iterator it = children.begin(); it != children.end(); it++) {
		ofPushMatrix();
		ofTranslate(position+contentPosition);
		(*it)->debugDraw();
		ofPopMatrix();
	}
}

void Box::calculateSize()
{
	Point parentSize;
	if(hasParent()){
		parentSize = getParent()->contentSize;
	}
	
	//get all the values
	float width = definition.width.getValueCalculated(parentSize.x);
	float height = definition.height.getValueCalculated(parentSize.y);
	
	float marginLeft = definition.marginLeft.getValueCalculated(parentSize.x);
	float marginRight = definition.marginRight.getValueCalculated(parentSize.x);
	float marginTop = definition.marginTop.getValueCalculated(parentSize.y);
	float marginBottom = definition.marginBottom.getValueCalculated(parentSize.y);
	
	float paddingLeft = definition.paddingLeft.getValueCalculated(parentSize.x);
	float paddingRight = definition.paddingRight.getValueCalculated(parentSize.x);
	float paddingTop = definition.paddingTop.getValueCalculated(parentSize.y);
	float paddingBottom = definition.paddingBottom.getValueCalculated(parentSize.y);
	
	float borderLeft = definition.borderLeft.getValueCalculated(parentSize.x);
	float borderRight = definition.borderRight.getValueCalculated(parentSize.x);
	float borderTop = definition.borderTop.getValueCalculated(parentSize.y);
	float borderBottom = definition.borderBottom.getValueCalculated(parentSize.y);
	
	size.x = width;
	size.y = height;
	outerSize.x = marginLeft + marginRight + size.x;
	outerSize.y = marginTop + marginBottom + size.y;
	contentSize.x = size.x - paddingLeft - paddingRight - borderLeft - borderRight;
	contentSize.y = size.y - paddingBottom - paddingTop - borderTop - borderBottom;
	contentPosition.x = paddingLeft + borderLeft;
	contentPosition.y = paddingTop + borderTop;
}

void Box::layout()
{
	calculateSize();
	Point position;
	float rowMaxHeight = 0;
	for(List::iterator it = children.begin(); it != children.end(); it++) {
		(*it)->layout();

		if(position.x + (*it)->outerSize.x > contentSize.x) {
			position.y += rowMaxHeight;
			position.x = 0;
			rowMaxHeight = 0;
		}
		
		(*it)->position = position + Point((*it)->definition.marginLeft.getValueCalculated(contentSize.x), (*it)->definition.marginTop.getValueCalculated(contentSize.y));

		position.x += (*it)->outerSize.x;
		
		if(rowMaxHeight < (*it)->outerSize.y) {
			rowMaxHeight = (*it)->outerSize.y;
		}
	}
}

void Box::definitionChanged(DefinitionEvent& e)
{
	getRootBox()->layout();
}

Box* Box::getParent()
{
	return parent;
}

Box* Box::getRootBox()
{
	Box* box = this;
	while(box->hasParent()) {
		box = box->getParent();
	}
	return box;
}

bool Box::hasParent()
{
	return bParent;
}

}
}
