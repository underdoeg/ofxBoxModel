#include "BoxConstrainer.h"
#include "components/BoxModel.h"

namespace boxModel
{
namespace tools
{

BoxConstrainer::BoxConstrainer()
{
	from = NULL;
	to = NULL;
}

BoxConstrainer::~BoxConstrainer()
{
}

void BoxConstrainer::set(boxModel::components::BoxDefinition* bd1, boxModel::components::BoxDefinition* bd2, bool useAbsolutePosition)
{
	remove();

	from = bd1;
	to = bd2;

	//copy current values
	to->size.set(from->size);
	to->outerSize.set(from->outerSize);
	to->contentSize.set(from->contentSize);

	to->position.set(from->position);
	if(useAbsolutePosition)
		to->position.set(from->getGlobalPosition());
	else
		to->position.set(from->position);

	to->contentPosition.set(from->contentPosition);

	//size
	from->size.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&to->size);
	from->outerSize.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&to->outerSize);
	from->contentSize.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&to->contentSize);

	//position
	if(useAbsolutePosition)
		from->globalPositionChanged.connect<BoxConstrainer, &BoxConstrainer::onGlobalPositionChanged>(this);
	else
		from->position.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&to->position);
	from->contentPosition.changed.connect<core::ValuePoint, &core::ValuePoint::set>(&to->contentPosition);

	if(to->components->hasComponent<boxModel::components::BoxModel>()) {
		to->components->getComponent<boxModel::components::BoxModel>()->setBoxDefinitionUpdate(false);
	}
}

void BoxConstrainer::onGlobalPositionChanged()
{
	to->position.set(from->getGlobalPosition());
}

void BoxConstrainer::remove()
{
	if(to == NULL || from == NULL)
		return;

	from->size.changed.disconnect<core::ValuePoint, &core::ValuePoint::set>(&to->size);
	from->outerSize.changed.disconnect<core::ValuePoint, &core::ValuePoint::set>(&to->outerSize);
	from->contentSize.changed.disconnect<core::ValuePoint, &core::ValuePoint::set>(&to->contentSize);

	//position
	from->globalPositionChanged.disconnect<BoxConstrainer, &BoxConstrainer::onGlobalPositionChanged>(this);
	from->position.changed.disconnect<core::ValuePoint, &core::ValuePoint::set>(&to->position);
	from->contentPosition.changed.disconnect<core::ValuePoint, &core::ValuePoint::set>(&to->contentPosition);
	if(to->components->hasComponent<boxModel::components::BoxModel>()) {
		to->components->getComponent<boxModel::components::BoxModel>()->setBoxDefinitionUpdate(true);
	}
}

}
}//end namespace
