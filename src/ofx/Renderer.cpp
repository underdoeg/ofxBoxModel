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

boxModel::core::RendererBase::ImagePointer Renderer::allocateImage(unsigned char* pixels, int width, int height, int bpp) {
	ofImage* img = new ofImage();
	ofImageType type = OF_IMAGE_GRAYSCALE;
	//if(bpp == 2)
	if(bpp == 3)
		type = OF_IMAGE_COLOR;
	else if(bpp == 4)
		type = OF_IMAGE_COLOR_ALPHA;
	if(width >0 && height > 0)
		img->setFromPixels(pixels, width, height, type);
	
	return (ImagePointer)img;
}

void Renderer::drawImage(ImagePointer img)
{
	if(!((ofImage*)img)->isAllocated())
		return;
	ofPushStyle();
	ofSetColor(255);
	((ofImage*)img)->draw(0, 0);
	ofPopStyle();
}

}} // end namespace

