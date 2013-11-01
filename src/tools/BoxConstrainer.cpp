#include "BoxConstrainer.h"
#include "components/BoxModel.h"

namespace boxModel
{
namespace tools
{

BoxConstrainer::BoxConstrainer(boxModel::components::BoxDefinition* bd1, boxModel::components::BoxDefinition* bd2)
{
	from = bd1;
	to = bd2;

	//copy current values
	to->size.set(from->size);
	to->outerSize.set(from->outerSize);
	to->contentSize.set(from->contentSize);

	to->position.set(from->position);
	to->contentPosition.set(from->contentPosition);

	//size
	from->size.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&bd2->size);
	from->outerSize.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&bd2->outerSize);
	from->contentSize.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&bd2->contentSize);

	//position
	from->position.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&bd2->position);
	from->contentPosition.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&bd2->contentPosition);

	if(to->components->hasComponent<boxModel::components::BoxModel>()){
		to->components->getComponent<boxModel::components::BoxModel>()->setBoxDefinitionUpdate(false);
	}
}

BoxConstrainer::~BoxConstrainer()
{
}

}
}//end namespace

