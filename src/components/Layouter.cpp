#include "Layouter.h"
#include "Splitter.h"
#include "Linker.h"

using namespace boxModel::components;
using namespace boxModel::core;

std::string Layouter::getName(){
	return "layouter";
}

void Layouter::setup() {

	stack = NULL;
	box = NULL;
	boxDefinition = NULL;
	isDirty = false;

	LISTEN_FOR_COMPONENT(Stack, Layouter, onStack)
	LISTEN_FOR_COMPONENT(BoxDefinition, Layouter, onBox)
	LISTEN_FOR_COMPONENT(BoxModel, Layouter, onBoxDefinition)
}

void Layouter::onStack(Stack* _stack) {
	stack = _stack;
	stack->childAdded.connect<Layouter, &Layouter::onChildAdded>(this);
	stack->childRemoved.connect<Layouter, &Layouter::onChildRemoved>(this);
}

void Layouter::onBox(BoxDefinition* _box) {
	box = _box;
	box->contentSize.changed.connect<Layouter, &Layouter::onContentSizeChanged>(this);
}

void Layouter::onBoxDefinition(BoxModel* box) {
	boxDefinition = box;
	boxDefinition->onHeightAuto.connect<Layouter, &Layouter::onAutoHeight>(this);
	boxDefinition->onWidthAuto.connect<Layouter, &Layouter::onAutoWidth>(this);
}

void Layouter::layout(bool layoutChildren) {
	
	preLayouted();
	
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
	
	//reset linked elements
	for(Stack * stackChild: stack->getChildren()) {
		if(stackChild->components->hasComponent<Linker>()){
			stackChild->components->getComponent<Linker>()->unlink();
		}
	}
	
	//merge splitted components before rearranging
	for(Stack * stackChild: stack->getChildren()) {
		if(stackChild->components->hasComponent<Splitter>()){
			if(stackChild->components->getComponent<Splitter>()->hasSplits)	
				stackChild->components->getComponent<Splitter>()->merge();
		}
	}
	
	std::string id  = components->getComponent<Addressable>()->getId();
		
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
	
	
	
	//place all elements
	for(Stack * stackChild: stack->getChildren()) {
		if(stackChild->components->hasComponent<BoxDefinition>()) {
			placeBox(stackChild->components->getComponent<BoxDefinition>());
		}
	}

	if(overflowElements.size()>0) {
		//these elements don't fit, maybe we can split them?
		Rectangle bounds;
		bounds.width = box->contentSize.x;
		bounds.height = box->contentSize.y;
		
		Rectangle childBounds;
		
		//loop a copy of the element list
		std::vector<ComponentContainer*> overflowElementsCopy = overflowElements;

		for(ComponentContainer* container: overflowElementsCopy) {
			//only check for overlapping if a splitter is present
			if(container->hasComponent<Splitter>()) {
				
				if(container->hasComponent<BoxDefinition>()) {
					BoxDefinition* child = container->getComponent<BoxDefinition>();
					childBounds.x = child->position.x;
					childBounds.y = child->position.y;
					childBounds.width = child->size.x;
					childBounds.height = child->size.y;
					if(bounds.intersects(childBounds)) {
						Rectangle r = bounds.getIntersection(childBounds);
						
						Splitter* splitter = container->getComponent<Splitter>();
						//request the split and if it happens, remove the component from overflow list and add the new splittet item
						if(splitter->requestSplit(r.width, r.height)) {
							
							std::vector<ComponentContainer*>::iterator itPos = std::find(overflowElements.begin(), overflowElements.end(), container);//std::remove(overflowElements.begin(), overflowElements.end(), container);
							overflowElements.erase(itPos);
							
							std::vector<ComponentContainer*> splits = splitter->getSplits();
							
							if(splits.size() == 2){
								stack->addChildFromContainer(splits[0]);
								overflowElements.insert(itPos, splits[1]);
							}else if(splits.size() == 1){
								overflowElements.insert(itPos, splits[0]);
							}
						}
					}
				}
			}
			//end check for splitter
		}
		//now if the size is still greater than 0, we can go ahead with the overflowed signal
		if(overflowElements.size() > 0)
			overflowed(overflowElements);
	}

	if(boxDefinition != NULL)
		boxDefinition->recalculateBoxSize();

	isDirty = false;
	
	//trigger layouted event
	layouted();
}

void Layouter::placeBox(BoxDefinition* childBox) {
	if(!childBox->components->hasComponent<BoxModel>())
		return;

	BoxModel* childBoxDef = childBox->components->getComponent<BoxModel>();

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
			//curPosition.x = 0;
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

void Layouter::triggerLayout() {
	isDirty = true;
}

void Layouter::onContentSizeChanged(core::Point p) {
	triggerLayout();
}

void Layouter::onChildRemoved(Stack* child) {
	if(child->components->hasComponent<BoxModel>()) {
		child->components->getComponent<BoxModel>()->floating.changed.disconnect<Layouter, &Layouter::onChildFloatingChanged>(this);
	}
	if(child->components->hasComponent<BoxDefinition>()) {
		child->components->getComponent<BoxDefinition>()->outerSize.changed.disconnect<Layouter, &Layouter::onChildSizeChanged>(this);
	}
	triggerLayout();
}

void Layouter::onChildAdded(Stack* child) {
	/*
	if(child->components->hasComponent<Splitter>()){
		if(child->components->getComponent<Splitter>()->hasSplits)
			return;
	}
	*/
	if(child->components->hasComponent<BoxModel>()) {
		BoxModel* boxDef = child->components->getComponent<BoxModel>();
		boxDef->floating.changed.connect<Layouter, &Layouter::onChildFloatingChanged>(this);
		boxDef->positioning.changed.connect<Layouter, &Layouter::onChildPositioningChanged>(this);
		boxDef->left.changed.connect<Layouter, &Layouter::onChildUnitChanged>(this);
		boxDef->top.changed.connect<Layouter, &Layouter::onChildUnitChanged>(this);
		boxDef->right.changed.connect<Layouter, &Layouter::onChildUnitChanged>(this);
		boxDef->bottom.changed.connect<Layouter, &Layouter::onChildUnitChanged>(this);
	}
	if(child->components->hasComponent<BoxDefinition>()) {
		BoxDefinition* childBox = child->components->getComponent<BoxDefinition>();
		childBox->outerSize.changed.connect<Layouter, &Layouter::onChildSizeChanged>(this);
		//placeBox(childBox);
		if(boxDefinition != NULL)
			boxDefinition->recalculateBoxSize();
	}
	triggerLayout();
}

void Layouter::onChildFloatingChanged(Floating floating) {
	triggerLayout();
}

void Layouter::onChildSizeChanged(core::Point p) {
	triggerLayout();
}

void Layouter::onChildPositioningChanged(Position p) {
	triggerLayout();
}

void Layouter::onChildUnitChanged(core::Unit* unit) {
	triggerLayout();
}

void Layouter::onAutoWidth(float& width) {
	if(stack == NULL)
		return;

	float maxW = 0;
	for(Stack* child: stack->getChildren()) {
		if(child->components->hasComponent<BoxDefinition>()) {
			BoxDefinition* childBox = child->components->getComponent<BoxDefinition>();
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
		if(child->components->hasComponent<BoxDefinition>()) {
			BoxDefinition* childBox = child->components->getComponent<BoxDefinition>();
			float r = childBox->position.y + childBox->size.y;
			if( r > maxH)
				maxH = r;
		}
	}
	if(maxH>height)
		height = maxH;
}
void Layouter::onFlush() {
	layout();
}

void Layouter::getInfo(core::Component::Info& info){

}