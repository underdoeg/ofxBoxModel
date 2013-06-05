#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "core/Component.h" // Base class: boxModel::src::Component

namespace boxModel
{

namespace components
{

template <class Type>
class BoxModel : public core::Component<Type>
{
public:
	COMPONENT()
	
	BoxModel(){};
	~BoxModel(){};
};

}

}

#endif // BOXMODEL_H
