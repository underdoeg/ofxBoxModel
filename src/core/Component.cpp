#include "Component.h"

namespace boxModel
{

namespace core
{

void componentDependencyWarning(std::string sender, std::string requirement){
	debug::warning(sender+" requires "+requirement);
}

Component::~Component()
{
	if(components == NULL)
		return;
	components->removeComponent(this);
}

}

}


