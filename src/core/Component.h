#ifndef COMPONENT_H
#define COMPONENT_H

#include <functional>
#include <iostream>
#include "debug/Print.h"

namespace boxModel {

namespace core {

class Test{
		
};

class ComponentBase {
public:
	~ComponentBase() {};
	virtual void registerComponent(ComponentBase& c) = 0;
};

template <class Type>
class HierarchyAccessor{
	
};

template <class Type>
class Component: public ComponentBase {
public:
	Component() {};
	~Component() {};

/*
	Type* getParentComponent() {
		return getParentFunction();
	}
	
	bool hasParentComponent() {
		return hasParentFunction();
	}
	
	int getNumChildrenComponent() {
		return getNumChildrenFunction();
	}
	
	Type* getChildComponent(int index){
		return getChildFunction(index);
	}
	
	std::function<bool(void)> hasParentFunction;
	std::function<Type*(void)> getParentFunction;
	std::function<int(void)> getNumChildrenFunction;
	std::function<Type*(int)> getChildFunction;
*/
	
private:
};

#define COMPONENT() void registerComponent(core::ComponentBase&){}; \
					Type* type;												\

//end namespace
}

}

#endif // COMPONENT_H
