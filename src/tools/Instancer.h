#ifndef INSTANCER_H
#define INSTANCER_H

#include "components/Addressable.h"
#include <unordered_map>
#include "Utils.h"

namespace boxModel {

namespace tools {


class InstancerHelperBase {
public:
	virtual core::ComponentContainer* create() = 0;
};

template <class InstanceType>
class InstancerHelper: public InstancerHelperBase {
public:
	InstanceType* create() {
		return new InstanceType();
	}
};


class Instancer {
public:
	Instancer();
	~Instancer();
	
	static void setup();
	
	template <class InstanceType>
	static void addInstancer(std::string name) {
		instancers[name] = new InstancerHelper<InstanceType>();
	}

	template <class InstanceType>
	static void addInstancer() {
		if(!checkIfInstanceable<InstanceType>()) {
			debug::error("Only Composite types are instanceable");
			return;
		}

		InstanceType inst;
		core::ComponentContainer* comp = &inst;
		if(!comp->hasComponent<components::Addressable>()) {
			debug::error("Only Composite types with the Addressable Component are instanceable");
			return;
		}

		instancers[comp->getComponent<components::Addressable>()->getType()] = new InstancerHelper<InstanceType>();
	}

	template <class InstanceType>
	static bool checkIfInstanceable() {
		return core::isBaseOf<core::ComponentContainer, InstanceType>::value;
	}
	
	static core::ComponentContainer* createInstance(std::string type){
		setup();
		if(instancers.find(type) == instancers.end()){
			debug::warning(type+" not found in instancers");
			return NULL;
		}
		return instancers[type]->create();
	}

private:
	static std::unordered_map<std::string, InstancerHelperBase*> instancers;
	static bool isSetup;
};

}

}


#endif // INSTANCER_H
