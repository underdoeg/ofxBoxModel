#ifndef LAYOUTABLE_H
#define LAYOUTABLE_H

#include "core/BoxModel.h"
#include "core/Utils.h"
#include "core/TreeNode.h"

namespace ofx {

namespace boxModel {

namespace core {

class LayoutableBase {
public:
	void setBoxPosition(core::BoxModel* b, core::Point p) {
		b->position.x = p.x;
		b->position.y = p.y;
		b->recalculate();
	}
};

template <class BoxModelType>
class Layoutable: public LayoutableBase {
public:
	Layoutable() {
		BoxModelType* box = crtpSelfPtr<Layoutable, BoxModelType>(this);

		//TODO: only listen to events that alter the size of a box
		//ofAddListener(box->changed, this, &Layoutable<BoxModelType>::onChange);
		ofAddListener(box->contentSize.changed, this, &Layoutable<BoxModelType>::onSizeChange);

		ofAddListener(box->childAdded, this, &Layoutable<BoxModelType>::onChildrenChange);
		ofAddListener(box->childRemoved, this, &Layoutable<BoxModelType>::onChildrenChange);
	}
	~Layoutable() {}

	virtual void layout() {
		curPosition.set(0,0);
		BoxModelType* t = crtpSelfPtr<Layoutable, BoxModelType>(this);
		for(typename core::TreeNode<BoxModelType>::ChildrenIterator it = t->childrenBegin(); it < t->childrenEnd(); it++) {
			//(*it)->layout();
			placeBox(*it, t);
			lastBox = *it;
			lastTypedBox = *it;
		}
	}

	virtual void placeTypedBox(BoxModelType* box, BoxModelType* thisBox){
		placeBox(box, thisBox);
	}

	virtual void placeBox(core::BoxModel* box, core::BoxModel* thisBox) {
		switch(box->floating) {
		case core::FloatLeft:
			if(curPosition.x + box->outerSize.x > thisBox->contentSize.x) {
				curPosition.x = 0;
				curPosition.y += rowMaxHeight;
				rowMaxHeight = 0;
			}
			curPosition += core::Point(box->marginLeft.getValueCalculated(), 0);
			setBoxPosition(box, curPosition + core::Point(0, box->marginTop.getValueCalculated()));
			curPosition.x += box->outerSize.x - box->marginLeft.getValueCalculated();
			break;
		case core::FloatRight:
			cout << "SORRY FLOAT RIGHT IS NOT IMPLEMENTED YET" << endl;
			break;
		default:
			curPosition.x = 0;
			curPosition.y += rowMaxHeight;
			rowMaxHeight = 0;

			setBoxPosition(box, curPosition + core::Point(box->marginLeft.getValueCalculated(), box->marginTop.getValueCalculated()));

			break;
		}

		if(rowMaxHeight < box->outerSize.y) {
			rowMaxHeight = box->outerSize.y;
		}
	}

protected:
	void onChange(BoxModel::Event& e){
		layout();
	}

	void onSizeChange(BoxModel::ReadOnlyPoint::Event& e){
		layout();
	}

	void onChildrenChange(typename core::TreeNode< BoxModelType >::Event& e){
		layout();
	}

	core::BoxModel* lastBox;
	BoxModelType* lastTypedBox;

private:
	core::Point curPosition;
	float rowMaxHeight;
};

}

}

}

#endif // LAYOUTABLE_H
