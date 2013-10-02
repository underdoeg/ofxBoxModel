#include "Stack.h"

namespace boxModel {

namespace components {

Stack::Stack():parent(NULL) {

}

void Stack::onDelete() {
	cout << "ON DELETE CALLED" << endl;
	if(hasParent()) {
		parent->removeChild(this);
	}
}

void Stack::setup() {
	parent = NULL;
}

void Stack::onFlush() {
	for(unsigned int i = 0; i < getNumChildren(); i++) {
		getChild(i)->components->flush();
	}
}

void Stack::onComponentAdded(Component& component) {

}

/**** BEGIN HIERARCHY FUNCTIONS ****/
void Stack::addChildren(std::vector<Stack*> children) {
	for(Stack* s: children) {
		addChild(s);
	}
}

void Stack::addChildren(std::vector<core::ComponentContainer*> compList) {
	for(core::ComponentContainer* comp: compList) {
		if(comp->hasComponent<Stack>()) {
			addChild(comp->getComponent<Stack>());
		}
	}
}

void Stack::addChildContainer(core::ComponentContainer* container) {
	if(container->hasComponent<Stack>())
		addChild(container->getComponent<Stack>());
}

void Stack::addChild(Stack* child) {
	if(child == NULL)
		return;
	if(child->getParent() == this)
		return;
	if(child->hasParent()) {
		child->getParent()->removeChild(child);
	}
	child->setParent(this);
	children.push_back(child);
	childAdded(child);
}

void Stack::addChildFromContainer(core::ComponentContainer* child) {
	if(child->hasComponent<Stack>()) {
		addChild(child->getComponent<Stack>());
	}
}

void Stack::removeChild(Stack* child) {
	if(std::find(children.begin(), children.end(), child)==children.end())
		return;
	child->parent = NULL;
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
	childRemoved(child);
}

void Stack::removeChildFromContainer(core::ComponentContainer* child) {
	if(child->hasComponent<Stack>()) {
		removeChild(child->getComponent<Stack>());
	}
}

void Stack::removeFromParent() {
	if(hasParent())
		parent->removeChild(this);
}

Stack* Stack::operator[](unsigned int index) {
	return getChild(index);
}

unsigned int Stack::getNumChildren() {
	return children.size();
}

Stack* Stack::getChild(unsigned int index) {
	assert(index < children.size());
	return children[index];
}

Stack::ChildrenIterator Stack::childrenBegin() {
	return children.begin();
}

Stack::ChildrenIterator Stack::childrenEnd() {
	return children.end();
}

bool Stack::hasParent() {
	return parent != NULL;
}

Stack* Stack::getParent() {
	return parent;
}

void Stack::setParent(Stack* p) {
	if(parent == p)
		return;
	removeFromParent();
	parent = p;
	if(p != NULL)
		parentChanged(p);
}

Stack::ChildrenList Stack::getChildren() {
	return children;
};

Stack* Stack::getUltimateParent() {
	if(!hasParent())
		return this;
	Stack* ret = getParent();
	while(ret->hasParent()) {
		ret = ret->getParent();
	}
	return ret;
}


}

}