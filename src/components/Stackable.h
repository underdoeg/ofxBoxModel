#ifndef STACKABLE_H
#define STACKABLE_H

#include "core/Component.h"
#include "assert.h"
#include "Utils.h"
#include "assert.h"

namespace boxModel {

namespace components {

class Stackable: public core::Component{
		public:
	
	typedef std::vector<Stackable*> 	ChildrenList;
	typedef ChildrenList::iterator 		ChildrenIterator;

	Stackable():parent(NULL) {
		
	}
	~Stackable() {
	}
	
	void setup(){
		
	}
	
	void onComponentAdded(Component& component){
		
	}
	
	/**** BEGIN HIERARCHY FUNCTIONS ****/
	void addChild(Stackable* child) {
		children.push_back(child);
	}

	void removeChild(Stackable* child) {
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}

	Stackable* operator[](unsigned int index) {
		return getChild(index);
	}

	int getNumChildren() {
		return children.size();
	}
	
	Stackable* getChild(unsigned int index) {
		assert(index < children.size());
		return children[index];
	}
	
	template <class Type>
	Type* getChild(unsigned int index){
		return core::castTo<Stackable, Type>(getChild(index));
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
	
	Stackable* getParent(){
		return parent;
	}
	
	void setParent(Stackable* p){
		parent = p;
	}
		
	ChildrenList getChildren(){
		return children;
	};
private:
	ChildrenList children;
	Stackable* parent;
};

}

}

#endif // STACKABLE_H
