#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "core/BoxModel.h"
#include <cassert>
#include "core/Utils.h"
#include "ofMain.h"

namespace ofx {

namespace boxModel {

namespace core {

/*****
* Templated container to stack BoxModels
****/

class TreeNodeBase {
public:
	virtual int getNumChildren()=0;
	virtual BoxModel* getBaseChild(int index)=0;
protected:
	std::vector<BoxModel*> childrenBase;
};

/*****
* Templated container to stack objects
****/

template <class BoxModelType>
class TreeNode {
public:
	typedef std::vector<BoxModelType*> ChildrenList;
	typedef typename ChildrenList::iterator ChildrenIterator;

	class Event: public ofEventArgs {
	public:
		Event(BoxModelType* d, BoxModelType* c) {
			sender = d;
			other = c;
		}
		BoxModelType* sender;
		BoxModelType* other;
	};

	TreeNode() {};
	~TreeNode() {};

	/** ITERATOR HELPERS **/
	ChildrenIterator childrenBegin() {
		return children.begin();
	}

	ChildrenIterator childrenEnd() {
		return children.end();
	}

	/***/
	BoxModelType* operator[](unsigned int index) {
		assert(index < children.size());
		return children[index];
	}

	void addChild(BoxModelType* child) {
		BoxModelType* bm = crtpSelfPtr<TreeNode, BoxModelType>(this);
		children.push_back(child);
		child->setParent(bm);
		Event e(bm, child);
		ofNotifyEvent(childAdded, e);
	}

	void removeChild(BoxModelType* child) {
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
		BoxModelType* bm = crtpSelfPtr<TreeNode, BoxModelType>(this);
		Event e(bm, child);
		ofNotifyEvent(childRemoved, e);
	}

	int getNumChildren() {
		return children.size();
	}

	BoxModelType* getChild(int index) {
		return children[index];
	}

	BoxModel* getBaseChild(int index) {
		return children[index];
	}

	ofEvent<Event> childAdded;
	ofEvent<Event> childRemoved;

private:
	void setParent(BoxModelType* p) {
		bParent = true;
		parent = parent;
	}

	ChildrenList children;
	bool bParent;
	BoxModelType* parent;
};

}

}

}

#endif // TREENODE_H
