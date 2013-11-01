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
	BoxConstrainer(boxModel::components::BoxDefinition* from, boxModel::components::BoxDefinition* to);
	~BoxConstrainer();

private:
	boxModel::components::BoxDefinition* from;
	boxModel::components::BoxDefinition* to;
};

}
}

#endif // BOXCONSTRAINER_H
