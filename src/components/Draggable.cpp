#include "Draggable.h"

namespace boxModel {

namespace components {

Draggable::Draggable() {
}

Draggable::~Draggable() {
}

std::string Draggable::getName() {
	return "draggable";
}

void Draggable::setup() {
	LISTEN_FOR_COMPONENT(Mouse, Draggable, onMouse)
	LISTEN_FOR_COMPONENT(BoxDefinition, Draggable, onBoxDefinition)
	LISTEN_FOR_COMPONENT(BoxModel, Draggable, onBoxModel)
	LISTEN_FOR_COMPONENT(Stack, Draggable, onStack)

	bFitInParent = true;
}

void Draggable::onBoxModel(BoxModel* bd) {
	boxModel = bd;
}

void Draggable::onBoxDefinition(BoxDefinition* bd) {
	boxDefinition = bd;
}

void Draggable::onStack(Stack* s) {
	stack = s;
}

void Draggable::onMouse(Mouse* m) {
	mouse = m;
	mouse->mousePress.connect<Draggable, &Draggable::onMousePress>(this);
	mouse->mouseDrag.connect<Draggable, &Draggable::onMouseDrag>(this);
	mouse->mouseDragOutside.connect<Draggable, &Draggable::onMouseDrag>(this);
}

void Draggable::onMouseDrag(float mouseX, float mouseY, boxModel::components::Mouse::ButtonStates& buttons) {
	if(!bDragging)
		return;

	core::Point pNew(mouseX, mouseY);
	core::Point pDelta =  pNew - lastPos;

	if(boxModel != NULL && boxDefinition != NULL) {
		boxModel->positioning = Position::Absolute;
		boxModel->left = boxDefinition->position.x + pDelta.x;
		boxModel->top = boxDefinition->position.y + pDelta.y;

		if(stack != NULL && stack->hasParent()) {
			stack->getParent()->components->flush();
		} else {
			components->flush();
		}
	} else if(boxDefinition != NULL) {
		boxDefinition->position.x = boxDefinition->position.x + pDelta.x;
		boxDefinition->position.y = boxDefinition->position.y + pDelta.y;
	}
}

void Draggable::onMousePress(float mouseX, float mouseY, int button) {
	bDragging = true;
	lastPos.set(mouseX, mouseY);
}

void Draggable::setDraggableFitInParent(bool state) {
	bFitInParent = state;
}

void Draggable::checkForParentFit() {
	//fit to parent?
	if(bFitInParent) {
		if(boxModel != NULL && boxDefinition != NULL) {
			if(stack != NULL && stack->hasParent()) {
				if(stack->getParent()->components->hasComponent<BoxDefinition>()) {
					BoxDefinition* parentBoxDef = stack->getParent()->components->getComponent<BoxDefinition>();

					//too big?
					if(boxModel->left + boxDefinition->size.x > parentBoxDef->contentSize.x)
						boxModel->left = parentBoxDef->contentSize.x - boxDefinition->size.x;
					if(boxModel->top + boxDefinition->size.y > parentBoxDef->contentSize.y)
						boxModel->top = parentBoxDef->contentSize.y - boxDefinition->size.y;

					//too small?
					if(boxModel->left < parentBoxDef->contentPosition.x)
						boxModel->left = parentBoxDef->contentPosition.x;
					if(boxModel->top < parentBoxDef->contentPosition.y)
						boxModel->top = parentBoxDef->contentPosition.y;
				}

			} else {

				if(boxModel->left < 0)
					boxModel->left = 0;
				if(boxModel->top < 0)
					boxModel->top = 0;
			}
		}
	}
}

void Draggable::onFlush()
{
	checkForParentFit();
}

}
}// end namespace

