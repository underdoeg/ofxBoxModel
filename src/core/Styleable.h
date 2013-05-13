#ifndef STYLEABLE_H
#define STYLEABLE_H

#include "BoxModel.h"
#include "core/TreeNode.h"

namespace ofx
{

namespace boxModel
{

namespace core
{

template <class BoxModelType>
class Styleable
{
public:
	Styleable() {
		color.set(0);
		bgColor.set(255);
	};
	
	~Styleable() {}
	
	void setColor(Color c) {
		color.set(c);
	}
	
	void setColor(int gray, int alpha=255){
		color.set(gray, alpha);
	}

	void setColor(int r, int g, int b, int alpha=255) {
		color.set(r, g, b, alpha);
	}

	Color getColor() {
		return color;
	}

	void setBgColor(Color c) {
		bgColor.set(c);
	}
	
	void setBgColor(int gray, int alpha=255){
		bgColor.set(gray, alpha);
	}

	void setBgColor(int r, int g, int b, int alpha=255) {
		bgColor.set(r, g, b, alpha);
	}

	Color getBgColor() {
		return bgColor;
	}
	
	void setColorChildren(Color c, bool recursive = true){
		BoxModelType* treeNode = crtpSelfPtr<Styleable, BoxModelType>(this);
		for(typename TreeNode<BoxModelType>::ChildrenIterator it=treeNode->childrenBegin();it<treeNode->childrenEnd();it++){
			(*it)->setColor(c);
			if(recursive){
				(*it)->setColorChildren(c, recursive);
			}
		}
	}

	void setBgColorChildren(Color c, bool recursive = true){
		BoxModelType* treeNode = crtpSelfPtr<Styleable, BoxModelType>(this);
		for(typename TreeNode<BoxModelType>::ChildrenIterator it=treeNode->childrenBegin();it<treeNode->childrenEnd();it++){
			(*it)->setBgColor(c);
			if(recursive){
				(*it)->setBgColorChildren(c, recursive);
			}
		}
	}

private:
	Color color;
	Color bgColor;
};

}

}

}

#endif // STYLEABLE_H
