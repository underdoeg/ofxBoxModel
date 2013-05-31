#ifndef INSTANCEABLE_H
#define INSTANCEABLE_H

#include <map>
#include <string>
#include "Addressable.h"

namespace boxModel
{

namespace core
{

template <class BoxModelType>
class InstancerBase
{
public:
	virtual BoxModelType* create() = 0;
};

template <class	BoxModelType>
class Instanceable
{
public:
	template <class InstanceType>
	class Instancer: public InstancerBase<BoxModelType>
	{
		BoxModelType* create() {
			return new InstanceType();
		}
	};

	Instanceable() {};
	~Instanceable() {};

	template <class InstanceType>
	static void addInstancer(std::string name) {
		instancers["name"] = new Instancer<InstanceType>;
	}

	template <class InstanceType>
	static void addInstancer(BoxModelType* box) {
		if(is_base_of<Addressable<BoxModelType>, BoxModelType>::value) {
			Addressable<BoxModelType>* b = (Addressable<BoxModelType>*)box;
			instancers[b->getType()] = new Instancer<InstanceType>;
		} else {
			debug::error("automatic instancer registration only works with Addressable types");
		}
	}

	template <class InstanceType>
	static void addInstancer() {
		if(is_base_of<Addressable<BoxModelType>, InstanceType>::value) {
			InstanceType b;
			addInstancer<InstanceType>(&b);
		} else {
			debug::warning("addType: InstanceType does not include the addressable type");
		}
	}

	static BoxModelType* createInstance(std::string name) {
		if(!hasBoxModelTypeInstancer) {
			addInstancer<BoxModelType>();
			hasBoxModelTypeInstancer = true;
		}
		if(instancers.count(name) == 1)
			return instancers[name]->create();
		else
			debug::warning("key '"+name+"' not found in instancers");
		return NULL;
	}

private:
	static std::map<std::string, InstancerBase<BoxModelType>*> instancers;
	static bool hasBoxModelTypeInstancer;
};

template<class BoxModelType>
std::map<std::string, InstancerBase<BoxModelType>*> Instanceable<BoxModelType>::instancers;

template<class BoxModelType>
bool Instanceable<BoxModelType>::hasBoxModelTypeInstancer = false;

}

}

#endif // INSTANCEABLE_H
