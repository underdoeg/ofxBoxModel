#ifndef LAYOUTER_H
#define LAYOUTER_H

#include "core/Component.h"
#include "components/Box.h"
#include "components/Stack.h"

namespace boxModel {

namespace components {

class Layouter: public core::Component {
public:

	void setup() {

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
protected:
	virtual void placeBox(Box* childBox) {
		if(!childBox->components->hasComponent<BoxDefinition>())
			return;

		BoxDefinition* childBoxDef = childBox->components->getComponent<BoxDefinition>();
		
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

		if(rowMaxHeight < childBox->outerSize.y) {
			rowMaxHeight = childBox->outerSize.y;
		}
	}

private:
	void onContentSizeChanged(core::Point p) {
		layout();
	}

	void onChildRemoved(Stack* child) {
		
		if(child->components->hasComponent<BoxDefinition>()){
			child->components->getComponent<BoxDefinition>()->floating.changed.disconnect<Layouter, &Layouter::onChildFloatingChanged>(this);
		}
		if(child->components->hasComponent<Box>()){
			child->components->getComponent<Box>()->outerSize.changed.disconnect<Layouter, &Layouter::onChildSizeChanged>(this);
		}
		layout();
	}

	void onChildAdded(Stack* child) {
		if(child->components->hasComponent<BoxDefinition>()){
			child->components->getComponent<BoxDefinition>()->floating.changed.connect<Layouter, &Layouter::onChildFloatingChanged>(this);
		}
		if(child->components->hasComponent<Box>()){
			child->components->getComponent<Box>()->outerSize.changed.connect<Layouter, &Layouter::onChildSizeChanged>(this);
		}
		layout();
	}
	
	void onChildFloatingChanged(Floating floating){
		layout();
	}	
	
	void onChildSizeChanged(core::Point p){
		layout();
	}
	
	void onAutoWidth(float& width){
		if(stack == NULL)
			return;
			
		float maxW = 0;
		for(Stack* child: stack->getChildren()){
			if(child->components->hasComponent<Box>()){
				Box* childBox = child->components->getComponent<Box>();
				float r = childBox->position.x + childBox->size.x;
				if( r > maxW)
					maxW = r;
			}
		}
		if(maxW>width)
			width = maxW;
	}
	
	void onAutoHeight(float& height){
		if(stack == NULL)
			return;
			
		float maxH = 0;
		for(Stack* child: stack->getChildren()){
			if(child->components->hasComponent<Box>()){
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
	//Box* lastBox;


	Stack* stack;
	Box* box;
	BoxDefinition* boxDefinition;
};

}

}

#endif // LAYOUTER_H
