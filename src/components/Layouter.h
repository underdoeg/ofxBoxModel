#ifndef LAYOUTER_H
#define LAYOUTER_H

#include "core/Component.h"
#include "components/Box.h"
#include "components/Stack.h"
#include "components/BoxDefinition.h"

namespace boxModel {

namespace components {

class Layouter: public core::Component {
public:

	void setup() {
		autoLayout = true;

		stack = NULL;
		box = NULL;
		boxDefinition = NULL;

		LISTEN_FOR_COMPONENT(Stack, Layouter, onStack)
		LISTEN_FOR_COMPONENT(Box, Layouter, onBox)
		LISTEN_FOR_COMPONENT(BoxDefinition, Layouter, onBoxDefinition)
	}

	void onStack(Stack* _stack) {
		stack = _stack;
		stack->childAdded.connect<Layouter, &Layouter::onChildAdded>(this);
		stack->childRemoved.connect<Layouter, &Layouter::onChildRemoved>(this);
	}

	void onBox(Box* _box) {
		box = _box;
		box->contentSize.changed.connect<Layouter, &Layouter::onContentSizeChanged>(this);
	}

	void onBoxDefinition(BoxDefinition* box) {
		boxDefinition = box;
		boxDefinition->onHeightAuto.connect<Layouter, &Layouter::onAutoHeight>(this);
		boxDefinition->onWidthAuto.connect<Layouter, &Layouter::onAutoWidth>(this);
	}

	virtual void layout() {
		if(stack == NULL || box == NULL)
			return;

		if(stack->getNumChildren() == 0)
			return;

		//this is the root box
		if(!stack->hasParent()) {
			if(boxDefinition != NULL) {
				box->position.set(boxDefinition->margin.left.getValueCalculated(), boxDefinition->margin.top.getValueCalculated()); //TODO: make this work
			}
		}

		maxContentSize.set(0, 0);
		curPosition.set(0,0);
		rowMaxHeight = 0;
		
		for(Stack * stackChild: stack->getChildren()) {
			if(stackChild->components->hasComponent<Box>()) {
				Box* child = stackChild->components->getComponent<Box>();
				placeBox(child);
			}
		}

		if(boxDefinition != NULL)
			boxDefinition->recalculateBoxSize();
	}
	
	Nano::signal<void(core::ComponentContainer*)> overflowed;
	
	bool autoLayout;
protected:
	virtual void placeBox(Box* childBox) {
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
				curPosition.x = 0;
				curPosition.y += rowMaxHeight;
				rowMaxHeight = 0;
				childBox->position.set(curPosition + core::Point(childBoxDef->margin.left.getValueCalculated(), childBoxDef->margin.top.getValueCalculated()));
				break;
			}

			if(boxDefinition->height != core::Unit::Auto && rowMaxHeight < childBox->outerSize.y) {
				rowMaxHeight = childBox->outerSize.y;
			}
			
			if(childBox->position.y + childBox->size.y > box->contentSize.y){
				//overflowed(childBox->components);
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

private:
	void onContentSizeChanged(core::Point p) {
		if(!autoLayout)
			return;
		layout();
	}

	void onChildRemoved(Stack* child) {

		if(child->components->hasComponent<BoxDefinition>()) {
			child->components->getComponent<BoxDefinition>()->floating.changed.disconnect<Layouter, &Layouter::onChildFloatingChanged>(this);
		}
		if(child->components->hasComponent<Box>()) {
			child->components->getComponent<Box>()->outerSize.changed.disconnect<Layouter, &Layouter::onChildSizeChanged>(this);
		}
		if(!autoLayout)
			return;
		layout();
	}

	void onChildAdded(Stack* child) {
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
		if(!autoLayout)
			return;
		layout();
	}

	void onChildFloatingChanged(Floating floating) {
		if(!autoLayout)
			return;
		layout();
	}

	void onChildSizeChanged(core::Point p) {
		if(!autoLayout)
			return;
		layout();
	}
	
	void onChildPositioningChanged(Position p) {
		if(!autoLayout)
			return;
		layout();
	}
	
	void onChildUnitChanged(core::Unit* unit) {
		if(!autoLayout)
			return;
		layout();
	}

	void onAutoWidth(float& width) {
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

	void onAutoHeight(float& height) {
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

	core::Point maxContentSize;
	core::Point curPosition;
	float rowMaxHeight;
	
	std::vector<core::ComponentContainer*> overflowElements;

	Stack* stack;
	Box* box;
	BoxDefinition* boxDefinition;
};

}

}

#endif // LAYOUTER_H
