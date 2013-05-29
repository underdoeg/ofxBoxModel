#ifndef STYLEABLE_H
#define STYLEABLE_H

#include "BoxModel.h"
#include "core/TreeNode.h"

namespace boxModel {

namespace core {

template <class BoxModelType>
class Styleable {
public:
	Styleable() {
		color.set(0);
		bgColor.set(255);
		borderColor.set(0);
		bBgColor = true;
	};

	~Styleable() {}

	void setColor(Color c) {
		color.set(c);
	}

	void setColor(int gray, int alpha=255) {
		color.set(gray, alpha);
	}

	void setColor(int r, int g, int b, int alpha=255) {
		color.set(r, g, b, alpha);
	}

	Color getColor() {
		return color;
	}

	void setBgColorNone() {
		bBgColor = false;
	}

	void setBgColor(Color c) {
		bgColor.set(c);
		bBgColor = true;
	}

	void setBgColor(int gray, int alpha=255) {
		bgColor.set(gray, alpha);
		bBgColor = true;
	}

	void setBgColor(int r, int g, int b, int alpha=255) {
		bgColor.set(r, g, b, alpha);
		bBgColor = true;
	}

	bool hasBgColor() {
		return bBgColor;
	}

	Color getBgColor() {
		return bgColor;
	}

	void setBorderColor(Color c) {
		borderColor.set(c);
	}

	void setBorderColor(int gray, int alpha=255) {
		borderColor.set(gray, alpha);
	}

	void setBorderColor(int r, int g, int b, int alpha=255) {
		borderColor.set(r, g, b, alpha);
	}

	Color getBorderColor() {
		return borderColor;
	}

	void setColorChildren(Color c, bool recursive = true) {
		BoxModelType* treeNode = crtpSelfPtr<Styleable, BoxModelType>(this);
		for(typename TreeNode<BoxModelType>::ChildrenIterator it=treeNode->childrenBegin(); it<treeNode->childrenEnd(); it++) {
			(*it)->setColor(c);
			if(recursive) {
				(*it)->setColorChildren(c, recursive);
			}
		}
	}

	void setBgColorChildren(Color c, bool recursive = true) {
		BoxModelType* treeNode = crtpSelfPtr<Styleable, BoxModelType>(this);
		for(typename TreeNode<BoxModelType>::ChildrenIterator it=treeNode->childrenBegin(); it<treeNode->childrenEnd(); it++) {
			(*it)->setBgColor(c);
			if(recursive) {
				(*it)->setBgColorChildren(c, recursive);
			}
		}
	}

private:
	Color color;
	Color bgColor;
	Color borderColor;
	bool bBgColor;
};

}

}

#endif // STYLEABLE_H
