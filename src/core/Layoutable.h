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

};

template <class BoxModelType>
class Layoutable: public LayoutableBase {
public:
	Layoutable() {
		BoxModelType* box = crtpSelfPtr<Layoutable, BoxModelType>(this);

		//TODO: only listen to events that alter the size of a box
		//ofAddListener(box->changed, this, &Layoutable<BoxModelType>::onChange);
		ofAddListener(box->contentSize.changed, this, &Layoutable<BoxModelType>::onSizeChange);

		ofAddListener(box->childAdded, this, &Layoutable<BoxModelType>::onChildAdded);
		ofAddListener(box->childRemoved, this, &Layoutable<BoxModelType>::onChildRemoved);

		ofAddListener(box->recalculated, this, &Layoutable<BoxModelType>::onRecalculate);
	}
	~Layoutable() {}

	virtual void layout() {
		maxContentSize.set(0, 0);
		curPosition.set(0,0);
		BoxModelType* t = crtpSelfPtr<Layoutable, BoxModelType>(this);
		for(typename core::TreeNode<BoxModelType>::ChildrenIterator it = t->childrenBegin(); it < t->childrenEnd(); it++) {
			//(*it)->layout();
			placeBox(*it, t);
			lastBox = *it;
			lastTypedBox = *it;
		}
		checkForAutoSize();
	}

	virtual void placeTypedBox(BoxModelType* box, BoxModelType* thisBox) {
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
			box->forcePosition(curPosition + core::Point(0, box->marginTop.getValueCalculated()));
			curPosition.x += box->outerSize.x - box->marginLeft.getValueCalculated();
			break;
		case core::FloatRight:
			debug::warning("SORRY FLOAT RIGHT IS NOT IMPLEMENTED YET");
			break;
		default:
			curPosition.x = 0;
			curPosition.y += rowMaxHeight;
			rowMaxHeight = 0;
			box->forcePosition(curPosition + core::Point(box->marginLeft.getValueCalculated(), box->marginTop.getValueCalculated()));
			break;
		}

		if(rowMaxHeight < box->outerSize.y) {
			rowMaxHeight = box->outerSize.y;
		}
	}

protected:
	void onChange(BoxModel::Event& e) {
		layout();
	}

	void onSizeChange(BoxModel::ReadOnlyPoint::Event& e) {
		layout();
	}

	void onChildAdded(typename core::TreeNode< BoxModelType >::Event& e) {
		ofAddListener(e.box->outerSize.changed, this, &Layoutable<BoxModelType>::onChildSizeChanged);
		layout();
	}

	void onChildRemoved(typename core::TreeNode< BoxModelType >::Event& e) {
		ofRemoveListener(e.box->outerSize.changed, this, &Layoutable<BoxModelType>::onChildSizeChanged);
		layout();
	}

	void onChildSizeChanged(BoxModel::ReadOnlyPoint::Event& e){
		layout();
	}

	void checkForAutoSize(){

		BoxModelType* t = crtpSelfPtr<Layoutable, BoxModelType>(this);

		if(t->width.getType() == Unit::Auto) {
			float maxW = 0;
			for(typename core::TreeNode<BoxModelType>::ChildrenIterator it = t->childrenBegin(); it < t->childrenEnd(); it++) {
				float r = (*it)->position.x + (*it)->size.x;
				if( r > maxW)
					maxW = r;
			}
			t->forceContentSize(maxW, t->contentSize.y);
		}
		if(t->height.getType() == Unit::Auto) {
			float maxH = 0;
			for(typename core::TreeNode<BoxModelType>::ChildrenIterator it = t->childrenBegin(); it < t->childrenEnd(); it++) {
				float r = (*it)->position.y + (*it)->size.y;
				if( r > maxH)
					maxH = r;
			}
			t->forceContentSize(t->contentSize.x, maxH);

		}
	}

	void onRecalculate(BoxModel::Event& e) {
		checkForAutoSize();
	}

	core::BoxModel* lastBox;
	BoxModelType* lastTypedBox;

private:
	core::Point maxContentSize;
	core::Point curPosition;
	float rowMaxHeight;
};

}

}

}

#endif // LAYOUTABLE_H
