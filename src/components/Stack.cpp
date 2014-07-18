#include "Stack.h"
#include "core/Utils.h"
#include "components/BoxDefinition.h"
#include "Style.h"

namespace boxModel {

namespace components {

Stack::Stack():parent(NULL) {

}

void Stack::onDelete() {
	if(hasParent()) {
		parent->removeChild(this);
	}
}

std::string Stack::getName() {
	return "stack";
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
	onChildAdded(child);
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
	onChildRemoved(child);
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
	if(index >= children.size())
		return NULL;
	//assert(index < children.size());
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

Stack::ChildrenList Stack::getChildrenRecursive() {
	Stack::ChildrenList ret;
	getChildrenRecursiveHelper(ret);
	return ret;
}

void Stack::getChildrenRecursiveHelper(ChildrenList& list) {
	appendChildrenToList(list);
	for(Stack* child: children) {
		child->getChildrenRecursiveHelper(list);
	}
}

void Stack::appendChildrenToList(ChildrenList& list) {
	list.insert(list.end(), children.begin(), children.end());
}

Stack* Stack::getUltimateParent() {
	if(!hasParent())
		return this;
	Stack* ret = getParent();
	while(ret->hasParent()) {
		ret = ret->getParent();
	}
	return ret;
}

bool Stack::isChildOf(Stack* item) {
	if(!hasParent())
		return false;
	if(getParent() == item)
		return true;
	return false;
}


void Stack::getInfo(core::Component::Info& info) {
	info["num children"] = core::toString(getNumChildren());
	//info["children"] = core::toString(getChildren())
	if(hasParent())
		info["parent"] = core::toString(getParent()->getId());
	else
		info["parent"] = "none";
}

boxModel::core::ComponentContainer* Stack::containerAt(float x, float y) {
	boxModel::core::ComponentContainer*  ret = NULL;
	if(components->hasComponent<BoxDefinition>()) {
		BoxDefinition* bd = components->getComponent<BoxDefinition>();

		for(unsigned int i=0; i<getNumChildren(); i++) {
			Stack* child = getChild(i);
			if(child->components->hasComponent<BoxDefinition>()) {
				BoxDefinition* childBox = child->components->getComponent<BoxDefinition>();
				bool visible = true;
				if(childBox->components->hasComponent<Style>()) {
					visible = child->components->getComponent<Style>()->isVisible();
				}
				if(visible && childBox->isInside(x, y)) {
					ret = child->containerAt(x - childBox->position.x, y - childBox->position.y);
				}
			}
		}
		if(ret == NULL && x < bd->size.x && y < bd->size.y) {
			ret = this->components;
		}
	} else {
		ret = this->components;
	}
	return ret;
}

Stack* Stack::nextInStack() {
	if(!hasParent())
		return NULL;
	
	int position = getParent()->getStackPosition(this);
	position++;
	return getParent()->getChild(position);
}

Stack* Stack::prevInStack() {
	if(!hasParent())
		return NULL;
	int position = getParent()->getStackPosition(this);
	position--;
	if(position < 0)
		return NULL;
	return getParent()->getChild(position);
	
}

int Stack::getStackPosition(Stack* child) {
	if(!child->isChildOf(this))
		return -1;
	return std::find(children.begin(), children.end(), child) - children.begin();
}

}
} //end namespace
