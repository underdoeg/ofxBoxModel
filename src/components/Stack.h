#ifndef STACKABLE_H
#define STACKABLE_H

#include "core/Component.h"
#include "assert.h"
#include "Utils.h"
#include "assert.h"
#include <algorithm>

namespace boxModel {

namespace components {

class Stack: public core::Component {
public:

	typedef std::vector<Stack*> 	ChildrenList;
	typedef ChildrenList::iterator 		ChildrenIterator;

	Stack():parent(NULL) {

	}
	~Stack() {
	}

	void setup() {

	}

	void onComponentAdded(Component& component) {

	}

	/**** BEGIN HIERARCHY FUNCTIONS ****/
	void addChildren(std::vector<Stack*> children){
		for(Stack* s: children){
			addChild(s);
		}
	}
	
	void addChildren(std::vector<core::ComponentContainer*> compList){
		for(core::ComponentContainer* comp: compList){
			if(comp->hasComponent<Stack>()){
				addChild(comp->getComponent<Stack>());
			}
		}
	}
	
	void addChild(Stack* child) {
		if(child->hasParent()){
			child->getParent()->removeChild(child);
		}
		child->setParent(this);
		children.push_back(child);
		childAdded(child);
	}

	void removeChild(Stack* child) {
		child->setParent(NULL);
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
		childRemoved(child);
	}

	Stack* operator[](unsigned int index) {
		return getChild(index);
	}

	unsigned int getNumChildren() {
		return children.size();
	}

	Stack* getChild(unsigned int index) {
		assert(index < children.size());
		return children[index];
	}

	template <class Type>
	Type* getChild(unsigned int index) {
		return core::castTo<Stack, Type>(getChild(index));
	}

	ChildrenIterator childrenBegin() {
		return children.begin();
	}

	ChildrenIterator childrenEnd() {
		return children.end();
	}

	bool hasParent() {
		return parent != NULL;
	}

	Stack* getParent() {
		return parent;
	}

	void setParent(Stack* p) {
		parent = p;
		if(p != NULL)
			parentChanged(p);
	}

	ChildrenList getChildren() {
		return children;
	};
	
	Stack* getUltimateParent(){
		if(!hasParent())
			return this;
		Stack* ret = getParent();
		while(ret->hasParent()){
			ret = ret->getParent();
		}
		return ret;
	}
	
	Nano::signal<void(Stack*)> childAdded;
	Nano::signal<void(Stack*)> childRemoved;
	Nano::signal<void(Stack*)> parentChanged;
	
private:
	ChildrenList children;
	Stack* parent;
};

}

}

#endif // STACKABLE_H
