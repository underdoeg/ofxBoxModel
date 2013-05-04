#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "core/BoxModel.h"

namespace ofx
{

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
	/*
	std::vector<BoxModel*> getChildrenBase() {
		return childrenBase;
	};*/
	virtual int getNumChildren()=0;
	virtual BoxModel* getBaseChild(int index)=0;
protected:
	std::vector<BoxModel*> childrenBase;
};

/*****
* Templated container to stack objects
****/

template <class BoxModelType>
class TreeNode: public TreeNodeBase
{
public:
	TreeNode() {};
	~TreeNode() {};
	void addChild(BoxModelType* child) {
		children.push_back(child);
		childrenChanged();
	}

	void removeChild(BoxModelType* child) {
		children.erase(std::remove(children.begin(), children.end(), child), children.end());
		childrenChanged();
	}
	
	int getNumChildren(){
		return children.size();
	}
	
	BoxModelType* getChild(int index){
		return children[index];
	}
	
	BoxModel* getBaseChild(int index){
		return children[index];
	}
private:
	void calculateSize(){
		Point p;
		if(bParent){
			p = parent->contentSize;
		}
		BoxModelType::calculateSize(p);
	}

	void childrenChanged() {
		childrenBase.clear();
		for(typename std::vector<BoxModelType*>::iterator it = children.begin(); it<children.end(); it++) {
			childrenBase.push_back(*it);
		}
	}
	std::vector<BoxModelType*> children;
	bool bParent;
	BoxModelType* parent;
};

}

}

}

#endif // TREENODE_H
