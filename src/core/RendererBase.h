#ifndef RENDERERBASE_H
#define RENDERERBASE_H

#include "core/BaseTypes.h"

namespace boxModel {

namespace core {

class RendererBase {
public:
	RendererBase();
	~RendererBase();
	
	virtual void pushMatrix() = 0;
	virtual void popMatrix() = 0;
	virtual void translate(boxModel::core::Point pos) = 0;
	virtual void drawRect(boxModel::core::Point position, boxModel::core::Point size, boxModel::core::Color color) = 0;
	virtual void drawLine(boxModel::core::Point a, boxModel::core::Point b, boxModel::core::Color color, float width) = 0;

	boxModel::core::Color bgColor;
	boxModel::core::Color color;
};

}

}

#endif // RENDERERBASE_H
