#ifndef IMAGE_H
#define IMAGE_H

#include "Box.h"

namespace boxModel {
namespace boxes {

class Image: public Box {
public:
	Image();
	~Image();

	string getType();
};

}
}

#endif // IMAGE_H
