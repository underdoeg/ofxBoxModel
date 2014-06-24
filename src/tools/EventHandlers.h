#ifndef EVENTHANDLERS_H
#define EVENTHANDLERS_H

#include <functional>
#include <map>

namespace boxModel {

namespace tools {
	
class EventHandlers {

public:
	
	static std::map<std::string, std::function<void(float, float, int)> > click;

};

}
}

#endif // EVENTHANDLERS_H
