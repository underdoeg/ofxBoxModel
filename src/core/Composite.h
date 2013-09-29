#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>
#include "debug/Print.h"
#include "Component.h"
#include "components/Addressable.h"
#include "Stack.h"

namespace boxModel {

namespace core {

class Composite: public ComponentContainer, public components::Addressable, public components::Stack {
public:
	Composite();
	
	virtual ~Composite();
	
	Composite* clone();
	
	template <class Type>
	Type* clone(){
		Type* t = new Type();
		cloneInto(t);
		return t;
	}
	
private:

};



}

}

#endif // COMPOSITE_H
