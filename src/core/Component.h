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
#include "Unit.h"

namespace boxModel {

namespace core {

class ComponentContainer;
	
class Component {
public:
	ComponentContainer* components;
	
	virtual void onFlush() {};

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
	
	virtual void flush(){};

public:
	typedef std::unordered_map<std::type_index, Component*> ComponentMap;
	
	unsigned int getNumComponents(){
		return componentList.size();
	}
	
	Component* getComponent(unsigned int index){
		return componentList[index];
	}
	
	template <class ComponentType>
	void addComponent(ComponentType* component) {
		std::type_index index = typeid(ComponentType);
		components[index] = component;
		componentList.push_back(component);
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
	
	void addUnitX(core::Unit* unit){
		units.push_back(unit);
		unitsX.push_back(unit);
	}
	
	void addUnitY(core::Unit* unit){
		units.push_back(unit);
		unitsY.push_back(unit);
	}
	
	void addUnitGroup(core::UnitGroup* unit){
		addUnitX(&unit->left);
		addUnitX(&unit->right);
		addUnitY(&unit->top);
		addUnitY(&unit->bottom);
	}
	
	void setUnitContainerSize(float x, float y){
		for(Unit* u:unitsX){
			u->setContainerSize(x);
		}
		for(Unit* u:unitsY){
			u->setContainerSize(y);
		}
	}

	private:
	std::vector<Unit*> units;
	std::vector<Unit*> unitsX;
	std::vector<Unit*> unitsY;
	
	std::unordered_map<std::type_index, Component*> components;
	std::unordered_map<std::type_index, ComponentSignalHelperBase*> componentAddedSignals;
	std::vector<Component*> componentList;
};

//the following is a macro that helps with listening to Component addition, ONLY USE WITHIN SETUP OF A COMPONENT
#define LISTEN_FOR_COMPONENT(ComponentType, ListenerClass, ListenerFunction) 																\
		if(components->hasComponent<ComponentType>())																					\
			ListenerFunction(components->getComponent<ComponentType>());																\
		else																															\
			components->getComponentAddedSignal<ComponentType>().connect<ListenerClass, &ListenerClass::ListenerFunction>(this);			\

//end namespace
}

}

#endif // COMPONENT_H
