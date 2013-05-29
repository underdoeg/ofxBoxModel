#ifndef INSTANCEABLE_H
#define INSTANCEABLE_H

#include <map>
#include <string>
#include "Addressable.h"

namespace boxModel {

namespace core {

template <class BoxModelType>
class InstancerBase {
	virtual BoxModelType* create() = 0;
};

template <class	BoxModelType>
class Instanceable {
public:
	template <class InstanceType>
	class Instancer: public InstancerBase<BoxModelType> {
		BoxModelType* create() {
			return new InstanceType();
		}
	};

	Instanceable() {};
	~Instanceable() {};

	template <class InstanceType>
	void addInstancer(std::string name) {
		instancers["name"] = new Instancer<InstanceType>;
	}

	template <class InstanceType>
	void addInstancer(BoxModelType* box) {
		if(is_base_of<Addressable<BoxModelType>, BoxModelType>::value) {
			Addressable<BoxModelType>* b = (Addressable<BoxModelType>*)box;
			instancers[b->getType()] = new Instancer<InstanceType>;
		} else {
			debug::error("automatic instancer registration only works with Addressable types");
		}
	}

private:
	static std::map<std::string, InstancerBase<BoxModelType>*> instancers;
};

template<class BoxModelType>
std::map<std::string, InstancerBase<BoxModelType>*> Instanceable<BoxModelType>::instancers;

}

}

#endif // INSTANCEABLE_H
