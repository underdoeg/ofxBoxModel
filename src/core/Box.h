#ifndef BOX_H
#define BOX_H

#include "core/BaseTypes.h"
#include "ofTypes.h"

namespace boxModel {

namespace core {

class Box {
public:
	Box();
	~Box();

	Value<Rectangle> outerRect;
	Value<Rectangle> innerRect;
	Value<Rectangle> contentRect;
};

}

}

#endif // BOX_H
