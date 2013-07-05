#include "Layouter.h"

using namespace boxModel::components;
using namespace boxModel::core;


void  Layouter::setup() {

	stack = NULL;
	box = NULL;
	boxDefinition = NULL;
	isDirty = false;

	LISTEN_FOR_COMPONENT(Stack, Layouter, onStack)
	LISTEN_FOR_COMPONENT(Box, Layouter, onBox)
	LISTEN_FOR_COMPONENT(BoxDefinition, Layouter, onBoxDefinition)
}

void  Layouter::onStack(Stack* _stack) {
	stack = _stack;
	stack->childAdded.connect<Layouter, &Layouter::onChildAdded>(this);
	stack->childRemoved.connect<Layouter, &Layouter::onChildRemoved>(this);
}

void  Layouter::onBox(Box* _box) {
	box = _box;
	box->contentSize.changed.connect<Layouter, &Layouter::onContentSizeChanged>(this);
}

void  Layouter::onBoxDefinition(BoxDefinition* box) {
	boxDefinition = box;
	boxDefinition->onHeightAuto.connect<Layouter, &Layouter::onAutoHeight>(this);
	boxDefinition->onWidthAuto.connect<Layouter, &Layouter::onAutoWidth>(this);
}

void  Layouter::layout(bool layoutChildren) {
	if(stack == NULL )
		return;

	if(stack->getNumChildren() == 0)
		return;

	if(layoutChildren) {
		for(Stack* child: stack->getChildren()) {
			if(child->components->hasComponent<Layouter>())
				child->components->getComponent<Layouter>()->layout(true);
		}
	}
	if(!isDirty || box == NULL)
		return;

	//this is the root box
	if(!stack->hasParent()) {
		if(boxDefinition != NULL) {
			box->position.set(boxDefinition->margin.left.getValueCalculated(), boxDefinition->margin.top.getValueCalculated()); //TODO: make this work
		}
	}

	maxContentSize.set(0, 0);
	curPosition.set(0, 0);
	rowMaxHeight = 0;
	overflowElements.clear();

	for(Stack * stackChild: stack->getChildren()) {
		if(stackChild->components->hasComponent<Box>()) {
			Box* child = stackChild->components->getComponent<Box>();
			placeBox(child);
		}
	}

	if(overflowElements.size()>0) {
		overflowed(overflowElements);
	}

	if(boxDefinition != NULL)
		boxDefinition->recalculateBoxSize();
	
	isDirty = false;
}


void Layouter::placeBox(Box* childBox) {
	if(!childBox->components->hasComponent<BoxDefinition>())
		return;

	BoxDefinition* childBoxDef = childBox->components->getComponent<BoxDefinition>();

	if(childBoxDef->positioning == Relative) {
		switch(childBoxDef->floating) {
		case Floating::FloatLeft:
			if(curPosition.x + childBox->outerSize.x > box->contentSize.x) {
				curPosition.x = 0;
				curPosition.y += rowMaxHeight;
				rowMaxHeight = 0;
			}
			curPosition += core::Point(childBoxDef->margin.left.getValueCalculated(), 0);
			childBox->position.set(curPosition + core::Point(0, childBoxDef->margin.top.getValueCalculated()));
			curPosition.x += childBox->outerSize.x - childBoxDef->margin.left.getValueCalculated();
			break;
		default:
			curPosition.x = box->contentPosition.x;
			curPosition.y += rowMaxHeight;
			rowMaxHeight = 0;
			childBox->position.set(curPosition + core::Point(childBoxDef->margin.left.getValueCalculated(), childBoxDef->margin.top.getValueCalculated()));
			break;
		}

		if(rowMaxHeight < childBox->outerSize.y) { //boxDefinition->height != core::Unit::Auto &&
			rowMaxHeight = childBox->outerSize.y;
		}


		if((childBox->position.y + childBox->size.y) > box->contentSize.y) {
			overflowElements.push_back(childBox->components);
		}
	} else if(childBoxDef->positioning == Absolute) {
		//TODO: could be optimized for less calculations
		core::Point p;
		core::Point p1 = core::Point(
		                     childBoxDef->left.getValueCalculated() + childBoxDef->margin.left.getValueCalculated(),
		                     childBoxDef->top.getValueCalculated() + childBoxDef->margin.top.getValueCalculated()
		                 );
		core::Point p2 = core::Point(
		                     box->contentSize.x - childBoxDef->right.getValueCalculated() - childBox->size.x + childBoxDef->margin.left.getValueCalculated(),
		                     box->contentSize.y - childBoxDef->bottom.getValueCalculated() - childBox->size.y + childBoxDef->margin.bottom.getValueCalculated()
		                 );
		if(childBoxDef->bottom.isSet() && childBoxDef->right.isSet()) {
			p = p2;
		} else if(childBoxDef->bottom.isSet()) {
			p = p1;
			p.y = p2.y;
		} else if(childBoxDef->right.isSet()) {
			p = p1;
			p.x = p2.x;
		} else {
			p = p1;
		}
		childBox->position.set(p);
	}
}

void  Layouter::triggerLayout() {
	isDirty = true;
}

void  Layouter::onContentSizeChanged(core::Point p) {
	triggerLayout();
}

void  Layouter::onChildRemoved(Stack* child) {

	if(child->components->hasComponent<BoxDefinition>()) {
		child->components->getComponent<BoxDefinition>()->floating.changed.disconnect<Layouter, &Layouter::onChildFloatingChanged>(this);
	}
	if(child->components->hasComponent<Box>()) {
		child->components->getComponent<Box>()->outerSize.changed.disconnect<Layouter, &Layouter::onChildSizeChanged>(this);
	}
	triggerLayout();
}

void  Layouter::onChildAdded(Stack* child) {
	if(child->components->hasComponent<BoxDefinition>()) {
		BoxDefinition* boxDef = child->components->getComponent<BoxDefinition>();
		boxDef->floating.changed.connect<Layouter, &Layouter::onChildFloatingChanged>(this);
		boxDef->positioning.changed.connect<Layouter, &Layouter::onChildPositioningChanged>(this);
		boxDef->left.changed.connect<Layouter, &Layouter::onChildUnitChanged>(this);
		boxDef->top.changed.connect<Layouter, &Layouter::onChildUnitChanged>(this);
		boxDef->right.changed.connect<Layouter, &Layouter::onChildUnitChanged>(this);
		boxDef->bottom.changed.connect<Layouter, &Layouter::onChildUnitChanged>(this);
	}
	if(child->components->hasComponent<Box>()) {
		Box* childBox = child->components->getComponent<Box>();
		childBox->outerSize.changed.connect<Layouter, &Layouter::onChildSizeChanged>(this);
		placeBox(childBox);
		if(boxDefinition != NULL)
			boxDefinition->recalculateBoxSize();
	}
	triggerLayout();
}

void  Layouter::onChildFloatingChanged(Floating floating) {
	triggerLayout();
}

void  Layouter::onChildSizeChanged(core::Point p) {
	triggerLayout();
}

void  Layouter::onChildPositioningChanged(Position p) {
	triggerLayout();
}

void  Layouter::onChildUnitChanged(core::Unit* unit) {
	triggerLayout();
}

void  Layouter::onAutoWidth(float& width) {
	if(stack == NULL)
		return;

	float maxW = 0;
	for(Stack* child: stack->getChildren()) {
		if(child->components->hasComponent<Box>()) {
			Box* childBox = child->components->getComponent<Box>();
			float r = childBox->position.x + childBox->size.x;
			if( r > maxW)
				maxW = r;
		}
	}
	if(maxW>width)
		width = maxW;
}

void Layouter::onAutoHeight(float& height) {
	if(stack == NULL)
		return;

	float maxH = 0;
	for(Stack* child: stack->getChildren()) {
		if(child->components->hasComponent<Box>()) {
			Box* childBox = child->components->getComponent<Box>();
			float r = childBox->position.y + childBox->size.y;
			if( r > maxH)
				maxH = r;
		}
	}
	if(maxH>height)
		height = maxH;
}
void Layouter::onFlush()
{
	layout();
}
