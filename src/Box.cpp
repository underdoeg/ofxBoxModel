#include "Box.h"


namespace ofx
{
namespace BoxModel
{

/*

Box::Box():bParent(false)
{
	ofAddListener(props.changed, this, &Box::propertyChanged);
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
	if(hasParent()) {
		parentSize = getParent()->contentSize;
	}

	//get all the values
	float width = props.width.getValueCalculated(parentSize.x);
	float height = props.height.getValueCalculated(parentSize.y);

	float marginLeft = props.marginLeft.getValueCalculated(parentSize.x);
	float marginRight = props.marginRight.getValueCalculated(parentSize.x);
	float marginTop = props.marginTop.getValueCalculated(parentSize.y);
	float marginBottom = props.marginBottom.getValueCalculated(parentSize.y);

	float paddingLeft = props.paddingLeft.getValueCalculated(parentSize.x);
	float paddingRight = props.paddingRight.getValueCalculated(parentSize.x);
	float paddingTop = props.paddingTop.getValueCalculated(parentSize.y);
	float paddingBottom = props.paddingBottom.getValueCalculated(parentSize.y);

	float borderLeft = props.borderLeft.getValueCalculated(parentSize.x);
	float borderRight = props.borderRight.getValueCalculated(parentSize.x);
	float borderTop = props.borderTop.getValueCalculated(parentSize.y);
	float borderBottom = props.borderBottom.getValueCalculated(parentSize.y);

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

		//position child relatively
		if((*it)->props.position == Properties::Relative) {
			if((*it)->props.floating == Properties::NoFloat) {
				//child has no floating, comes on the next line
				position.y += rowMaxHeight;
				position.x = 0;
				rowMaxHeight = 0;

				(*it)->position = position + Point((*it)->props.marginLeft.getValueCalculated(contentSize.x), (*it)->props.marginTop.getValueCalculated(contentSize.y));

			} else if((*it)->props.floating == Properties::Left) {
				//child float left
				if(position.x + (*it)->outerSize.x > contentSize.x || (*it)->props.clear == true) {
					position.y += rowMaxHeight;
					position.x = 0;
					rowMaxHeight = 0;
				}

				(*it)->position = position + Point((*it)->props.marginLeft.getValueCalculated(contentSize.x), (*it)->props.marginTop.getValueCalculated(contentSize.y));

				position.x += (*it)->outerSize.x;
			}
		} else if((*it)->props.position == Properties::Absolute) { //calculate absolute position
			Point p;
			Point p1 =  Point(
							  (*it)->props.left.getValueCalculated(contentSize.x) + (*it)->props.marginLeft.getValueCalculated(contentSize.x),
							  (*it)->props.top.getValueCalculated(contentSize.y) + (*it)->props.marginTop.getValueCalculated(contentSize.y)
						  ); 
			Point p2 =  Point(
							  contentSize.x - (*it)->props.right.getValueCalculated(contentSize.x) - (*it)->size.x + (*it)->props.marginLeft.getValueCalculated(contentSize.x),
							  contentSize.y - (*it)->props.bottom.getValueCalculated(contentSize.y) - (*it)->size.y + (*it)->props.marginBottom.getValueCalculated(contentSize.y)
						  ); 
			//check for left, bottom first, then bottom, then left and default is right & top
			if((*it)->props.bottom.isSet() && (*it)->props.right.isSet()){
				p = p2;
			}else if((*it)->props.bottom.isSet()){
				p = p1;
				p.y = p2.y;
			}else if((*it)->props.right.isSet()){
				p = p1;
				p.x = p2.x;
			}else{
				p = p1;
			}
			
			(*it)->position = p;
		}

		if(rowMaxHeight < (*it)->outerSize.y) {
			rowMaxHeight = (*it)->outerSize.y;
		}
	}
}

void Box::propertyChanged(Properties::Event& e)
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

 */

}
}
