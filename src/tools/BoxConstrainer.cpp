#include "BoxConstrainer.h"

namespace boxModel
{
namespace tools
{

BoxConstrainer::BoxConstrainer(boxModel::components::BoxDefinition* bd1, boxModel::components::BoxDefinition* bd2)
{
	box1 = bd1;
	box2 = bd2;

	//box1->size.changed
}

BoxConstrainer::~BoxConstrainer()
{
}

}
}//end namespace

