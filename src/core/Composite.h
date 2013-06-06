#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>
#include "debug/Print.h"
#include "Component.h"

namespace boxModel {

namespace core {

class Composite: public ComponentContainer {
public:
	
	/**** END HIERARCHY FUNCTIONS ****/

	template <class... Components>
	void registerComponents(Components... components) {
		registerComponent(components...);
		
		std::tuple<Components...> tuple(components...);
	}

private:
	template <class ComponentType, class... Rest>
	void registerComponent(ComponentType& t, Rest... rest){
		registerComponent<ComponentType>(t);
		registerComponent(rest...);
	}


};



}

}

#endif // COMPOSITE_H
