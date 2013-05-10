#ifndef LAYOUTER_H
#define LAYOUTER_H

#include "core/TreeNode.h"

namespace ofx {

namespace boxModel {

namespace layout {

class LayouterBase {
public:

	//virtual void layout(core::TreeNodeBase* t) = 0;
	void setBoxPosition(core::BoxModel* b, core::Point p) {
		b->position.x = p.x;
		b->position.y = p.y;
		b->recalculate();
	}
};

template <class BoxModelType>
class Layouter: public LayouterBase {
public:
	virtual void layout(core::TreeNode<BoxModelType>* t) {
		for(typename core::TreeNode<BoxModelType>::ChildrenIterator it = t->childrenBegin(); it < t->childrenEnd(); it++) {
			layout(*it);
			placeBox(*it);
			lastBox = *it;
		}
	}

	virtual void placeBox(core::BoxModel* box) {
		switch(box->floating) {
		case core::FloatLeft:
			curPosition += core::Point(0, 0);
			setBoxPosition(box, curPosition);
			curPosition.x += box->outerSize.x;
			break;
		case core::FloatRight:
			cout << "SORRY FLOAT RIGHT IS NOT IMPLEMENTED YET" << endl;
			break;
		default:
			curPosition.x = 0;
			curPosition.y += rowMaxHeight;
			rowMaxHeight = 0;

			setBoxPosition(box, curPosition);

			break;
		}


		if(rowMaxHeight < box->outerSize.y) {
			rowMaxHeight = box->outerSize.y;
		}
	}

protected:
	core::BoxModel* lastBox;
	core::BoxModel* lastParentBox;
private:
	core::Point curPosition;
	float rowMaxHeight;
};

}

}

}

#endif // LAYOUTER_H
