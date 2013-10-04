#include "Renderer.h"

namespace boxModel {

namespace ofx {

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::popMatrix() {
	ofPopMatrix();
}

void Renderer::pushMatrix() {
	ofPushMatrix();
}

void Renderer::translate(boxModel::core::Point pos) {
	ofTranslate(pos);
}

void Renderer::drawLine(boxModel::core::Point a, boxModel::core::Point b, boxModel::core::Color color, float width) {
	ofPushStyle();
	ofSetLineWidth(width);
	ofSetColor(color);
	ofLine(a, b);
	ofPopStyle();
}

void Renderer::drawRect(boxModel::core::Point position, boxModel::core::Point size, boxModel::core::Color color) {
	ofPushStyle();
	ofFill();
	ofSetColor(color);
	ofRect(position, size.x, size.y);
	ofPopStyle();
}

}} // end namespace

