#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "core/Component.h" // Base class: boxModel::src::Component

namespace boxModel
{

namespace components
{

class BoxModel : public core::Component
{
public:
	//COMPONENT()
	
	BoxModel(){};
	~BoxModel(){};
	
	void setup();
};

}

}

#endif // BOXMODEL_H
