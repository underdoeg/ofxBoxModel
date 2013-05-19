#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "core/BoxModel.h"
#include <cassert>
#include "core/Utils.h"
#include "ofMain.h"

namespace boxModel
{

namespace core
{

/*****
* Templated container to stack BoxModels
****/

class TreeNodeBase
{
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
class TreeNode
{
public:
	typedef std::vector<BoxModelType*> ChildrenList;
	typedef typename ChildrenList::iterator ChildrenIterator;

	class Event: public ofEventArgs
	{
	public:
		Event(BoxModelType* d, BoxModelType* c) {
			sender = d;
			box = c;
		}
		BoxModelType* sender;
		BoxModelType* box;
	};

	TreeNode() {
		BoxModelType* box = crtpSelfPtr<TreeNode, BoxModelType>(this);
		ofAddListener(box->recalculated, this, &TreeNode<BoxModelType>::onRecalculate);
		ofAddListener(box->contentSize.changed, this, &TreeNode<BoxModelType>::onSizeChange);

		ofAddListener(box->childAdded, this, &TreeNode<BoxModelType>::onChildAdded);
		ofAddListener(box->childRemoved, this, &TreeNode<BoxModelType>::onChildRemoved);
	};
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
	void updateContainerSizes() {
		BoxModelType* t = crtpSelfPtr<TreeNode, BoxModelType>(this);
		float w = t->contentSize.x;
		float h = t->contentSize.y;

		BoxModel* b;
		for(typename core::TreeNode<BoxModelType>::ChildrenIterator it = t->childrenBegin(); it < t->childrenEnd(); it++) {
			b = *it;
			b->width.setContainerSize(w);
			b->height.setContainerSize(h);

			b->marginLeft.setContainerSize(w);
			b->marginRight.setContainerSize(w);
			b->marginTop.setContainerSize(h);
			b->marginBottom.setContainerSize(h);

			b->paddingLeft.setContainerSize(w);
			b->paddingRight.setContainerSize(w);
			b->paddingTop.setContainerSize(h);
			b->paddingBottom.setContainerSize(h);

			b->borderLeft.setContainerSize(w);
			b->borderRight.setContainerSize(w);
			b->borderTop.setContainerSize(h);
			b->borderBottom.setContainerSize(h);
			
			b->recalculate();
		}
	}

	void onChildAdded(typename core::TreeNode< BoxModelType >::Event& e) {
		updateContainerSizes();
	}

	void onChildRemoved(typename core::TreeNode< BoxModelType >::Event& e) {

	}

	void onRecalculate(BoxModel::Event& e) {
	}

	void onSizeChange(BoxModel::ReadOnlyPoint::Event& e) {
		updateContainerSizes();
	}

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

#endif // TREENODE_H
