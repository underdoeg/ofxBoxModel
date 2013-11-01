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
	BoxConstrainer();
	~BoxConstrainer();

	void set(boxModel::components::BoxDefinition* from, boxModel::components::BoxDefinition* to, bool useAbsolutePosition = false);
	void remove();
private:
	void onGlobalPositionChanged();
	boxModel::components::BoxDefinition* from;
	boxModel::components::BoxDefinition* to;
};

}
}

#endif // BOXCONSTRAINER_H
