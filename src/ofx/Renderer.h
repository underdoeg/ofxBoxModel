#ifndef RENDERER_H
#define RENDERER_H

#include "core/RendererBase.h"
#include "ofMain.h"

namespace boxModel {

namespace ofx {

class Renderer: public boxModel::core::RendererBase {
	public:

	Renderer();
	~Renderer();

	void drawLine(boxModel::core::Point a, boxModel::core::Point b, boxModel::core::Color color, float width);
	void drawRect(boxModel::core::Point position, boxModel::core::Point size, boxModel::core::Color color);
	void popMatrix();
	void pushMatrix();
	void translate(boxModel::core::Point pos);
	virtual ImagePointer allocateImage(unsigned char* pixels, int width, int height, int bpp);
	virtual void drawImage(ImagePointer img);

};

}

}

#endif // RENDERER_H
