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
	void addChild(Stack* child) {
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

	int getNumChildren() {
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
	}

	ChildrenList getChildren() {
		return children;
	};
	
	Stack* getUltimateParent(){
		
	}
	
	Nano::signal<void(Stack*)> childAdded;
	Nano::signal<void(Stack*)> childRemoved;
	
private:
	ChildrenList children;
	Stack* parent;
};

}

}

#endif // STACKABLE_H
