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
	size.x = definition.width;
	size.y = definition.height;
	outerSize.x = definition.marginLeft + definition.marginRight + size.x;
	outerSize.y = definition.marginTop + definition.marginBottom + size.y;
	contentSize.x = size.x - definition.paddingLeft - definition.paddingRight - definition.borderLeft - definition.borderRight;
	contentSize.y = size.y - definition.paddingBottom - definition.paddingTop - definition.borderTop - definition.borderBottom;
	contentPosition.x = definition.paddingLeft + definition.borderLeft;
	contentPosition.y = definition.paddingTop + definition.borderTop;
}

void Box::layout()
{
	calculateSize();
	Point position;
	Box* last = NULL;
	float rowMaxHeight = 0;
	for(List::iterator it = children.begin(); it != children.end(); it++) {
		(*it)->layout();

		if(position.x + (*it)->outerSize.x > contentSize.x) {
			position.y += rowMaxHeight;
			position.x = 0;
			rowMaxHeight = 0;
		}
		
		(*it)->position = position + Point((*it)->definition.marginLeft, (*it)->definition.marginTop);

		position.x += (*it)->outerSize.x;
		
		if(rowMaxHeight < (*it)->outerSize.y) {
			rowMaxHeight = (*it)->outerSize.y;
		}

		last = *it;
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
