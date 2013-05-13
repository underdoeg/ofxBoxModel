#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "core/BoxModel.h"
#include "core/TreeNode.h"
#include "core/Utils.h"
#include "core/Styleable.h"
#include "core/Addressable.h"

namespace ofx {

namespace boxModel {

namespace debug {

#define CHECK_FOR_TYPE(TYPE) core::is_base_of<core::TYPE<TreeNodeType>, TreeNodeType>::value>

template <class BoxModelType>
class DebugDrawer {
public:

	class DrawableBase {
	public:
		virtual void drawBox(BoxModelType* box) = 0;
	};

	template <class BoxFeature>
	class Drawable: public DrawableBase {
	public:

		void drawBox(BoxModelType* box) {
			drawBox((BoxFeature*)box, box);  //TODO: this casting is an ugly hack to be able to compile all different (incompatible) drawers
		};

		virtual void drawBox(BoxFeature* box, core::BoxModel* boxModel) = 0;
	};

	class DrawBoxModel: public Drawable<core::BoxModel>{
		virtual void drawBox(core::BoxModel* box, core::BoxModel* boxModel){

		}
	};

	class DrawStyleable: public Drawable<core::Styleable<BoxModelType> > {
	public:
		virtual void drawBox(core::Styleable<BoxModelType>* box, core::BoxModel* boxModel) {
			box->getColor();
		}
	};

	class DrawAddressable: public Drawable<core::Addressable<BoxModelType> > {
	public:
		virtual void drawBox(core::Addressable<BoxModelType>* box, core::BoxModel* boxModel) {

		}
	};

	DebugDrawer() {
		//styled box or basic box?
		if(core::is_base_of<core::Styleable<BoxModelType>, BoxModelType>::value) {
			drawers.push_back(new DrawStyleable());
		}else{
			drawers.push_back(new DrawBoxModel());
		}

		//add addressable drawer
		if(core::is_base_of<core::Addressable<BoxModelType>, BoxModelType>::value) {
			drawers.push_back(new DrawAddressable());
		}
	}
	~DebugDrawer() {}


	void drawTree(BoxModelType* rootNode) {
		drawBox(rootNode);
		for(typename BoxModelType::ChildrenIterator it = rootNode->childrenBegin(); it < rootNode->childrenEnd(); it++) {
			drawTree(*it);
		}
	}

	void drawBox(BoxModelType* box) {

		


		ofPushStyle();
		ofFill();
		ofSetColor(200);
		ofRect(box->position, box->size.x, box->size.y);

		ofNoFill();
		ofSetColor(70);
		ofRect(box->position, box->size.x, box->size.y);

		ofLine(box->position + box->contentPosition, box->position + box->contentPosition + box->contentSize);
		ofLine(box->position + box->contentPosition + core::Point(box->contentSize.x, 0), box->position + box->contentPosition + core::Point(0, box->contentSize.y));

		ofPopStyle();
	}

private:
	std::vector<DrawableBase*> drawers;
};

}

}

}

#endif // DEBUGDRAW_H
