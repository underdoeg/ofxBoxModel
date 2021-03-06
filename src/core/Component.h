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
#include "BaseTypes.h"
#include <map>

namespace boxModel {

namespace core {

class ComponentContainer;

class Component {
public:
	ComponentContainer* components;

	typedef std::map<std::string, std::string> Info;

	virtual void onDelete() {};
	virtual void onFlush() {};
	virtual void copyFrom(Component* component) {};
	virtual std::string getName() = 0;
	virtual void getInfo(Info& info){};

	unsigned int getId();

protected:
	Component();
	~Component();

	virtual void setup() {};

private:
	static unsigned int curID;
	unsigned int id;
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
	class ComponentSignalHelper : public ComponentSignalHelperBase {
	public:
		Nano::Signal<void(ComponentType*)> signal;
	};

	class CloneHelperBase {
	public:
		virtual void cloneComponentInto(ComponentContainer* source, ComponentContainer* destination) = 0;
	};

	template <class ComponentType>
	class CloneHelper: public CloneHelperBase {
	public:
		void cloneComponentInto(ComponentContainer* source, ComponentContainer* destination) {
			ComponentType* comp;
			if(!destination->hasComponent<ComponentType>()) {
				comp = new ComponentType();
				destination->addComponent<ComponentType>(comp);
			} else {
				comp = destination->getComponent<ComponentType>();
			}
			comp->copyFrom(source->getComponent<ComponentType>());
		}
	};

public:
	ComponentContainer() {
		disabled = false;
	}

	virtual ~ComponentContainer(){
		sendDelete();
	}

	void sendDelete(){
		for(unsigned int i = 0; i < getNumComponents(); i++) {
			getComponent(i)->onDelete();
		}
		deleted(this);
	}

	void flush() {
		preFlushed();
		for(unsigned int i = 0; i < getNumComponents(); i++) {
			getComponent(i)->onFlush();
		}
		postFlushed();
	};

	ComponentContainer* clone() {
		cout << "CLONE ALARM!" << endl;
		ComponentContainer* ret = new ComponentContainer();
		cloneInto(ret);
		return ret;
	}

	void cloneInto(ComponentContainer* container) {
		for(CloneHelperBase* ch: cloneHelpers) {
			ch->cloneComponentInto(this, container);
		}
	}

	typedef std::unordered_map<std::type_index, Component*> ComponentMap;

	unsigned int getNumComponents() {
		return componentList.size();
	}

	Component* getComponent(unsigned int index) {
		return componentList[index];
	}

	template <class ComponentType>
	void addComponent(ComponentType* component) {
		if(hasComponent<ComponentType>()) {
			debug::notice("skipped duplicate component type");
			return;
		}
		std::type_index index = typeid(ComponentType);
		components[index] = component;
		componentList.push_back(component);
		((Component*)component)->setup(this);

		//add a clone helper fot this type
		cloneHelpers.push_back(new CloneHelper<ComponentType>());

		//dispatch the component added event if we have listeners
		if(componentAddedSignals.find(index) != componentAddedSignals.end()) {
			static_cast<ComponentSignalHelper<ComponentType>*>(componentAddedSignals[index])->signal(component);
		}
	}

	template <class ComponentType>
	ComponentType* getComponent() {
		//assert(hasComponent<ComponentType>() && "component type not found");
		return static_cast<ComponentType*>(components[typeid(ComponentType)]);
	}

	template <class ComponentType>
	bool hasComponent() {
		if(components.size() == 0)
			return false;
		return components.find(typeid(ComponentType)) != components.end();
	}

	void removeComponent(Component* component){
		std::unordered_map<std::type_index, Component*>::iterator pos = components.end();
		for(std::unordered_map<std::type_index, Component*>::iterator it = components.begin(); it != components.end();it++){
			if(it->second == component){
				pos = it;
				break;
			}
		}
		if(pos != components.end())
			components.erase(pos);
	}

	//return a signal to attach to a specific component creation
	template <class ComponentType>
	Nano::Signal<void(ComponentType*)>& getComponentAddedSignal() {
		std::type_index index = typeid(ComponentType);
		if(componentAddedSignals.find(index) == componentAddedSignals.end()) {
			ComponentSignalHelper<ComponentType>* comp = new ComponentSignalHelper<ComponentType>();
			componentAddedSignals[index] = comp;
			return comp->signal;
		}
		return static_cast<ComponentSignalHelper<ComponentType>*>(componentAddedSignals[index])->signal;
	}

	void addUnitX(core::Unit* unit) {
		units.push_back(unit);
		unitsX.push_back(unit);
	}

	void addUnitY(core::Unit* unit) {
		units.push_back(unit);
		unitsY.push_back(unit);
	}

	void addUnitGroup(core::UnitGroup* unit) {
		addUnitX(&unit->left);
		addUnitX(&unit->right);
		addUnitY(&unit->top);
		addUnitY(&unit->bottom);
	}

	void setUnitContainerSize(float x, float y) {
		for(Unit* u:unitsX) {
			u->setContainerSize(x);
		}
		for(Unit* u:unitsY) {
			u->setContainerSize(y);
		}
	}
	
	void logInfo();
	
	virtual void onLoadComplete(){};

	Value<bool> disabled;

	Nano::Signal<void(ComponentContainer*)> deleted;

	Nano::Signal<void()> preFlushed;
	Nano::Signal<void()> postFlushed;

private:
	std::vector<Unit*> units;
	std::vector<Unit*> unitsX;
	std::vector<Unit*> unitsY;

	std::unordered_map<std::type_index, Component*> components;
	std::unordered_map<std::type_index, ComponentSignalHelperBase*> componentAddedSignals;
	std::vector<Component*> componentList;
	std::vector<CloneHelperBase*> cloneHelpers;
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
