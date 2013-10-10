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

	Stack();

	std::string getName();

	void onDelete();

	void setup();

	void onFlush();

	void onComponentAdded(Component& component);

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

	ChildrenIterator childrenBegin();
	ChildrenIterator childrenEnd();

	bool hasParent();
	Stack* getParent();
	void setParent(Stack* p);

	ChildrenList getChildren();
	ChildrenList getChildrenRecursive();
	Stack* getUltimateParent();

	void getInfo(core::Component::Info& info);

	boxModel::core::ComponentContainer* containerAt(float x, float y);

	Nano::signal<void(Stack*)> childAdded;
	Nano::signal<void(Stack*)> childRemoved;
	Nano::signal<void(Stack*)> parentChanged;

private:
	void appendChildrenToList(ChildrenList& list);
	void getChildrenRecursiveHelper(ChildrenList& list);

	ChildrenList children;
	Stack* parent;
};

}

}

#endif // STACKABLE_H
