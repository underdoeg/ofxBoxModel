#ifndef BOXCONSTRAINER_H
#define BOXCONSTRAINER_H

#include "components/BoxDefinition.h"

namespace boxModel
{
namespace tools
{

class BoxConstrainer
{
public:
	BoxConstrainer(boxModel::components::BoxDefinition* bd1, boxModel::components::BoxDefinition* bd2);
	~BoxConstrainer();

private:
	boxModel::components::BoxDefinition* box1;
	boxModel::components::BoxDefinition* box2;
};

}
}

#endif // BOXCONSTRAINER_H
