#include "Component.h"

namespace boxModel
{

namespace core
{

void componentDependencyWarning(std::string sender, std::string requirement){
	debug::warning(sender+" requires "+requirement);
}

unsigned int Component::curID = 0;

Component::Component():components(NULL) {
	id = curID;
	curID++;
};

Component::~Component()
{
	if(components == NULL)
		return;
	components->removeComponent(this);
}

}

}


