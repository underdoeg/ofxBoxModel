#ifndef BOX_H
#define BOX_H

#include "core/BaseTypes.h"

namespace boxModel {

namespace core {

class Box {
public:
	Box();
	~Box();

	Rectangle outerRect;
	Rectangle innerRect;
	Rectangle contentRect;
};

}

}

#endif // BOX_H
