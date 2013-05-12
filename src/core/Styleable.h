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
	Styleable(){};
	~Styleable(){};
	
	void setColor(Color c){
		
	}
	
	void setColor(int r, int g, int b, int alpha=255){
		
	}
	
	void setBackgroundColor(Color c){
		
	}
	
	void setBackgroundColor(int r, int g, int b, int alpha=255){
		
	}
	
	//TODO templated Property to store colors
};

}

}

}

#endif // STYLEABLE_H
