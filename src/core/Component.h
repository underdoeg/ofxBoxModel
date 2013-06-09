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
#include "nano_signal_slot.hpp"

namespace boxModel {

namespace core {

class ComponentContainer;

class Component {
public:
	ComponentContainer* components;

protected:
	Component():components(NULL) {};
	~Component() {};
	virtual void setup() {};

private:
	friend class ComponentContainer;
	void setup(ComponentContainer* c) {
		components = c;
		setup();
	};
};

void componentDependencyWarning(std::string sender, std::string requirement);

class ComponentContainer {
private:

	class ComponentSignalHelperBase {
	public:
	};

	template<class ComponentType>
	class ComponentSignalHelper : public ComponentSignalHelperBase{
	public:
		Nano::signal<void(ComponentType*)> signal;
	};

public:
	typedef std::unordered_map<std::type_index, Component*> ComponentMap;

	template <class ComponentType>
	void addComponent(ComponentType* component) {
		std::type_index index = typeid(ComponentType);
		components[index] = component;
		((Component*)component)->setup(this);
		//dispatch the component added event if we have listeners
		if(componentAddedSignals.find(index) != componentAddedSignals.end()){
			static_cast<ComponentSignalHelper<ComponentType>*>(componentAddedSignals[index])->signal(component);
		}
	}

	template <class ComponentType>
	ComponentType* getComponent() {
		assert(hasComponent<ComponentType>() && "component type not found");
		return static_cast<ComponentType*>(components[typeid(ComponentType)]);
	}

	template <class ComponentType>
	bool hasComponent() {
		return components.find(typeid(ComponentType)) != components.end();
	}
	
	//return a signal to attach to a specific component creation
	template <class ComponentType>
	Nano::signal<void(ComponentType*)>& getComponentAddedSignal() {
		std::type_index index = typeid(ComponentType);
		if(componentAddedSignals.find(index) == componentAddedSignals.end()){
			ComponentSignalHelper<ComponentType>* comp = new ComponentSignalHelper<ComponentType>();
			componentAddedSignals[index] = comp;
			return comp->signal;
		}
		return static_cast<ComponentSignalHelper<ComponentType>*>(componentAddedSignals[index])->signal;
	}

private:
	std::unordered_map<std::type_index, Component*> components;
	std::unordered_map<std::type_index, ComponentSignalHelperBase*> componentAddedSignals;
};

//the following is a macro that helps with listening to Component addition, ONLY USE WITHIN SETUP OF A COMPONENT
#define LISTEN_FOR_COMPONENT(ComponentType, ListenerType, ListenerFunction) 																\
		if(components->hasComponent<ComponentType>())																					\
			ListenerFunction(components->getComponent<ComponentType>());																\
		else																															\
			components->getComponentAddedSignal<ComponentType>().connect<ListenerType, &ListenerType::ListenerFunction>(this);			\

//end namespace
}

}

#endif // COMPONENT_H
