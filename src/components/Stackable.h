#ifndef STACKABLE_H
#define STACKABLE_H

#include "core/Component.h"

namespace boxModel {

namespace components {

template <class Type>
class Stackable {
public:
	COMPONENT()
	
	typedef typename std::vector<Type*>::iterator ChildrenIterator;

	Stackable():parent(NULL) {
	}
	~Stackable() {
	}
	
	/**** BEGIN HIERARCHY FUNCTIONS ****/
	void addChild(Type* child) {
		children.push_back(child);
	}

	void removeChild(Type* child) {
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}

	Type* operator[](unsigned int index) {
		getChild(index);
	}

	int getNumChildren() {
		return children.size();
	}

	Type* getChild(unsigned int index) {
		assert(index < children.size());
		return children[index];
	}

	ChildrenIterator childrenBegin() {
		return children.begin();
	}

	ChildrenIterator childrenEnd() {
		return children.end();
	}
	
	bool hasParent(){
		return parent != NULL;
	}
	
	Type* getParent(){
		return parent;
	}
	
	void setParent(Type* p){
		parent = p;
	}
	
	std::vector<Type*> children;
	Type* parent;
};

}

}

#endif // STACKABLE_H
