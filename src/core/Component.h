#ifndef COMPONENT_H
#define COMPONENT_H

#include <functional>
#include <iostream>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include "debug/Print.h"
#include "Utils.h"
#include "assert.h"

namespace boxModel {

namespace core {

class ComponentContainer;

class Component {
public:

protected:
	Component():componentContainer(NULL) {};
	~Component() {};
	virtual void setup() = 0;
	ComponentContainer* componentContainer;

private:
	friend class ComponentContainer;
	void setup(ComponentContainer* c) {componentContainer = c;};
};

template<class ComponentType, class Type>
class TypedComponent{
protected:
	TypedComponent() {
		const bool valid = core::isBaseOf<ComponentType, Type>::value;
		assert(valid && "Typed Component: the type provided must be a child of the component");
	}

	Type* getAsType() {
		return static_cast<Type*>(this);
	};
};

class ComponentContainer {
public:
	typedef std::unordered_map<std::type_index, Component*> ComponentMap;

	template <class ComponentType>
	void addComponent(ComponentType* component) {
		components[typeid(ComponentType)] = component;
	}

	template <class ComponentType>
	ComponentType* getComponent() {
		return static_cast<ComponentType*>(components[typeid(ComponentType)]);
	}

	template <class ComponentType>
	bool hasComponent() {
		return true;
	}

	void setupComponents() {
		for(auto& comp: components) {
			comp.second->setup(this);
		}
	}

private:
	std::unordered_map<std::type_index, Component*> components;
};

//end namespace
}

}

#endif // COMPONENT_H
