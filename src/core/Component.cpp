#include "Component.h"

namespace boxModel
{

namespace core
{

void componentDependencyWarning(std::string sender, std::string requirement){
	debug::warning(sender+" requires "+requirement);
}
	
}

}

