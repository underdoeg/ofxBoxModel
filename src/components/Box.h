#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "core/Component.h" // Base class: boxModel::src::Component
#include "core/BaseTypes.h"

namespace boxModel
{

namespace components
{

class Box : public core::Component
{
public:
	//COMPONENT()
	
	Box(){};
	~Box(){};
	
	void setup(){
		
	}
	
	core::ValuePoint position;
	core::ValuePoint outerSize;
	core::ValuePoint size;
	core::ValuePoint contentSize;
	core::ValuePoint contentPosition;
};

}

}

#endif // BOXMODEL_H
