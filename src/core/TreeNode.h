#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "core/BoxModel.h"
#include <cassert>
#include "core/Utils.h"

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
class TreeNode{
public:
	typedef std::vector<BoxModelType*> ChildrenList;
	typedef typename ChildrenList::iterator ChildrenIterator;

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
		children.push_back(child);
		child->setParent(crtpSelfPtr<TreeNode, BoxModelType>(this));
		//childrenChanged();
	}

	void removeChild(BoxModelType* child) {
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
		//childrenChanged();
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

private:
	void setParent(BoxModelType* p){
		bParent = true;
		parent = parent;
	}

	/*
	void childrenChanged() {
		childrenBase.clear();
		for(typename std::vector<BoxModelType*>::iterator it = children.begin(); it<children.end(); it++) {
			childrenBase.push_back(*it);
		}
	}
	 * */
	ChildrenList children;
	bool bParent;
	BoxModelType* parent;
};

}

}

}

#endif // TREENODE_H
