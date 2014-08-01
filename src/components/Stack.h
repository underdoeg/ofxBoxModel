#ifndef STACKABLE_H
#define STACKABLE_H

#include "core/Component.h"
#include "assert.h"
#include "Utils.h"
#include "assert.h"
#include <algorithm>


namespace boxModel {

namespace components {

class Stack: public boxModel::core::Component {
public:

	typedef std::vector<Stack*> 	ChildrenList;
	typedef ChildrenList::iterator 		ChildrenIterator;

	Stack();

	std::string getName();

	void onDelete();

	void setup();

	void onFlush();

	void onComponentAdded(boxModel::core::Component& component);

	/**** BEGIN HIERARCHY FUNCTIONS ****/
	void addChildren(std::vector<Stack*> children);
	void addChildren(std::vector<core::ComponentContainer*> compList);

	void addChildContainer(core::ComponentContainer* container);
	void addChild(Stack* child);
	void addChildFromContainer(core::ComponentContainer* child);

	void removeChild(Stack* child);
	void removeChildFromContainer(core::ComponentContainer* child);
	void removeFromParent();

	unsigned int getNumChildren();
	Stack* operator[](unsigned int index);
	Stack* getChild(unsigned int index);

	template <class Type>
	Type* getChild(unsigned int index) {
		return core::castTo<Stack, Type>(getChild(index));
	}
	
	template <class Type>
	std::vector<Type*> getChildren() {
		return core::castArrayTo<Stack, Type>(getChildren());
	}
	
	template <class Type>
	std::vector<Type*> getChildrenRecursive() {
		return core::castArrayTo<Stack, Type>(getChildrenRecursive());
	}
	
	template <class Type>
	std::vector<Type*> getChildrenComponents(bool recursive=false){
		std::vector<Type*> ret;
		std::vector<Stack*> children;
		
		if(recursive)
			children = getChildrenRecursive();
		else
			children = getChildren();
			
		for(Stack* child: children){
			if(child->components->hasComponent<Type>()){
				ret.push_back(child->components->getComponent<Type>());
			}
		}
			
		return ret;
	}

	ChildrenIterator childrenBegin();
	ChildrenIterator childrenEnd();
	
	
	//parent handling
	bool hasParent();
	Stack* getParent();
	void setParent(Stack* p);
	bool isChildOf(Stack* item);
	
	ChildrenList getChildren();
	ChildrenList getChildrenRecursive();
	Stack* getUltimateParent();

	void getInfo(core::Component::Info& info);
	
	//helpers
	template <class Type>
	Type* childAt(float x, float y) {
		return core::castTo<Stack, Type>(containerAt(x, y));
	}
	boxModel::core::ComponentContainer* containerAt(float x, float y);
	
	template <class Type>
	Type* nextInStack() {
		Stack* next = nextInStack();
		if(!next)
			return NULL;
		Type* ret = core::castTo<Stack, Type>(next);
		if(ret)
			return ret;
		return next->nextInStack<Type>();
	}
	Stack* nextInStack();
	
	template <class Type>
	Type* prevInStack() {
		Stack* prev = prevInStack();
		if(!prev)
			return NULL;
		Type* ret = core::castTo<Stack, Type>(prev);
		if(ret)
			return ret;
		return prev->prevInStack<Type>();
	}
	Stack* prevInStack();
	
	void moveToTopInStack();
	
	virtual void onChildAdded(Stack* child){};
	virtual void onChildRemoved(Stack* child){};
	
	
	
	Nano::Signal<void(Stack*)> childAdded;
	Nano::Signal<void(Stack*)> childRemoved;
	Nano::Signal<void(Stack*)> parentChanged;
	
	
private:
	void moveChildToTop(Stack* child);
	void appendChildrenToList(ChildrenList& list);
	void getChildrenRecursiveHelper(ChildrenList& list);
	int getStackPosition(Stack* child);

	ChildrenList children;
	Stack* parent;
};

}

}

#endif // STACKABLE_H
