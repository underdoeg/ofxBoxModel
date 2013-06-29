#include "Composite.h"

namespace boxModel
{

namespace core
{


Composite::Composite()
{
		addComponent<boxModel::components::Stack>(this);
		addComponent<boxModel::components::Addressable>(this);
}


}

}

