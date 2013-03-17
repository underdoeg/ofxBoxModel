#ifndef BOXLAYOUTER_H
#define BOXLAYOUTER_H

#include "Box.h" // Base class: ofx::BoxModel::Box

namespace ofx
{

namespace BoxModel
{

class Layouter : public ofx::BoxModel::Box
{
public:
	Layouter();
	~Layouter();

};

}

}

#endif // BOXLAYOUTER_H
