#include "EventHandlers.h"

namespace boxModel
{

namespace tools
{

std::map<std::string, std::function<void(float mouseX, float mouseY, int button)> > EventHandlers::click;


}

}

