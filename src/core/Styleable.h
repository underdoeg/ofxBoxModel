#ifndef STYLEABLE_H
#define STYLEABLE_H

#include "BoxModel.h"

namespace ofx
{

namespace boxModel
{

namespace core
{

template <class BoxModelType>
class Styleable
{
public:
	Styleable() {};
	~Styleable() {};

	void setColor(Color c) {
		color.set(c);
	}

	void setColor(int r, int g, int b, int alpha=255) {
		color.set(r, g, b, alpha);
	}

	Color getColor(){
		return color;
	}

	void setBackgroundColor(Color c) {
		bgColor.set(c);
	}

	void setBackgroundColor(int r, int g, int b, int alpha=255) {
		bgColor.set(r, g, b, alpha);
	}
	
private:
	Color color;
	Color bgColor;
};

}

}

}

#endif // STYLEABLE_H
