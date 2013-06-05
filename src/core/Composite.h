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

/**********************  TUPLE EACH WITH EACH *************************************/
template<class TupleType, size_t N, size_t N2>
struct tupleEachWithEach {
	static void call(TupleType& t) {
		if(N != N2)
			std::get<N>(t).registerComponent(std::get<N2>(t));
		tupleEachWithEach<TupleType, N-1, N2>::call(t);
	}
};

template<class TupleType, size_t N>
struct tupleEachWithEach<TupleType, 0, N> {
	static void call(TupleType& t) {
		std::get<0>(t).registerComponent(std::get<N>(t));
		tupleEachWithEach<TupleType, std::tuple_size<TupleType>::value-1, N-1>::call(t);
	}
};

template<class TupleType>
struct tupleEachWithEach<TupleType, 0, 0> {
	static void call(TupleType& t) {
	}
};

template<class TupleType>
void registerComponentsWithEachOther(TupleType t) {
	tupleEachWithEach<TupleType, std::tuple_size<TupleType>::value-1, std::tuple_size<TupleType>::value-1>::call(t);
}
/********************** END TUPLE EACH WITH EACH *************************************/


template <class Type>
class Composite {
public:
	
	/**** END HIERARCHY FUNCTIONS ****/

	template <class... Components>
	void registerComponents(Components... components) {
		registerComponent(components...);
		
		std::tuple<Components...> tuple(components...);
		registerComponentsWithEachOther<std::tuple<Components...> >(tuple);
	}

private:
	template <class ComponentType, class... Rest>
	void registerComponent(ComponentType& t, Rest... rest){
		registerComponent<ComponentType>(t);
		registerComponent(rest...);
	}
	
	template <class ComponentType>
	void registerComponent(ComponentType& t){
		t.type = static_cast<Type*>(this);
		/*
		t.hasParentFunction = std::bind(&Composite<Type>::hasParent, this);
		t.getParentFunction = std::bind(&Composite<Type>::getParent, this);
		t.getNumChildrenFunction = std::bind(&Composite<Type>::getNumChildren, this);
		t.getChildFunction = std::bind(&Composite<Type>::getChild, this, std::placeholders::_1);
		*/
	}

	std::vector<Type*> children;
	
	Type* parent;
};



}

}

#endif // COMPOSITE_H
