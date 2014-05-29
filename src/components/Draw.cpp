#include "Draw.h"

namespace boxModel {

namespace components {

class DummyRenderer: public boxModel::core::RendererBase {
public:
	virtual ImagePointer allocateImage(unsigned char* pixels, int width, int height, int bpp) {
		return NULL;
	}
	virtual void drawImage(ImagePointer img) {}
	virtual void drawLine(boxModel::core::Point a, boxModel::core::Point b, boxModel::core::Color color, float width) {}
	virtual void drawRect(boxModel::core::Point position, boxModel::core::Point size, boxModel::core::Color color) {}
	virtual void popMatrix() {}
	virtual void pushMatrix() {}
	virtual void translate(boxModel::core::Point pos) {}
};

boxModel::core::RendererBase* Draw::renderer = new DummyRenderer();

Draw::Draw() {
	style = NULL;
}

Draw::~Draw() {
}

std::string Draw::getName() {
	return "draw";
}

void Draw::setup() {
	bDrawDecorators = True;
	LISTEN_FOR_COMPONENT(BoxDefinition, Draw, onBoxDefinition)
	LISTEN_FOR_COMPONENT(Style, Draw, onStyle)
	LISTEN_FOR_COMPONENT(Stack, Draw, onStack)
	LISTEN_FOR_COMPONENT(BoxModel, Draw, onBoxModel)
}

void Draw::onBoxDefinition(BoxDefinition* bd) {
	boxDefinition = bd;
}

void Draw::onBoxModel(BoxModel* bm) {
	boxModel = bm;
}

void Draw::onStack(Stack* s) {
	stack = s;
}

void Draw::onStyle(Style* s) {
	style = s;
}

void Draw::setRenderer(core::RendererBase* r) {
	renderer = r;
}

boxModel::core::RendererBase* Draw::getRenderer() {
	return renderer;
}

void Draw::draw() {

	if(style != NULL)
		if(style->display == Style::DisplayType::NONE || style->display == Style::DisplayType::HIDDEN)
			return;

	preDraw();
	preDrawRef(this);

	if(renderer != NULL && boxDefinition != NULL) {
		renderer->pushMatrix();
		renderer->translate(boxDefinition->position);
		drawDecorators();
		renderer->translate(boxDefinition->contentPosition);
	}

	onDraw();
	onDrawRef(this);

	customDraw();
	if(stack != NULL) {
		for(unsigned int i=0; i<stack->getNumChildren(); i++) {
			Stack* child = stack->getChild(i);
			if(child->components->hasComponent<Draw>())
				child->components->getComponent<Draw>()->draw();
		}
	}

	postDraw();
	postDrawRef(this);

	if(renderer != NULL && boxDefinition != NULL) {
		renderer->popMatrix();
	}
}

void Draw::drawDecorators() {
	if(renderer == NULL || boxDefinition == NULL)
		return;
	//BACKGROUND
	if(style != NULL) {
		if(style->hasBgColor()) {
			renderer->drawRect(core::Point(0, 0), boxDefinition->size, style->getBgColor());
		}
	}

	//BORDER
	bool drawBorderTop = false, drawBorderLeft = false, drawBorderRight = false, drawBorderBottom = false;
	float borderTopWidth, borderLeftWidth, borderBottomWidth, borderRightWidth;

	if(boxModel != NULL && style != NULL) {
		if(boxModel->border.top.getType() != core::Unit::Type_None) {
			drawBorderTop = true;
			borderTopWidth = boxModel->border.top.getValueCalculated();
		}
		if(boxModel->border.left.getType() != core::Unit::Type_None) {
			drawBorderLeft = true;
			borderLeftWidth = boxModel->border.left.getValueCalculated();
		}
		if(boxModel->border.right.getType() != core::Unit::Type_None) {
			drawBorderRight = true;
			borderRightWidth = boxModel->border.right.getValueCalculated();
		}
		if(boxModel->border.bottom.getType() != core::Unit::Type_None) {
			drawBorderBottom = true;
			borderBottomWidth = boxModel->border.bottom.getValueCalculated();
		}

		if(drawBorderTop) {
			renderer->drawRect(core::Point(0, 0), core::Point(boxDefinition->size.x, borderTopWidth), style->getBorderColor());
		}
		if(drawBorderLeft) {
			renderer->drawRect(core::Point(0, 0), core::Point(borderLeftWidth, boxDefinition->size.y), style->getBorderColor());
		}
		if(drawBorderRight) {
			renderer->drawRect(core::Point(boxDefinition->size.x - borderRightWidth, 0), core::Point(borderRightWidth, boxDefinition->size.y), style->getBorderColor());
		}
		if(drawBorderBottom) {
			renderer->drawRect(core::Point(0, boxDefinition->size.y - borderBottomWidth), core::Point(boxDefinition->size.x, borderBottomWidth), style->getBorderColor());
		}
	}
}

void Draw::customDraw() {

}

}
} //end namespace
