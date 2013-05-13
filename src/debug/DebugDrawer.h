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

/*********************************************************************************************************************/

void drawBoxInner(core::BoxModel* box, core::Color fg, core::Color bg);
void drawBoxOuter(core::BoxModel* box, core::Color fg, core::Color bg);

/********************************************************************************************************************/

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
			drawBox((BoxFeature*)box, box);  //TODO: this casting is an evil hack! But it is ok for now because this is only the debug drawer and not core
		};

		virtual void drawBox(BoxFeature* box, core::BoxModel* boxModel) = 0;
	};

	class DrawBoxModel: public Drawable<core::BoxModel>{
		virtual void drawBox(core::BoxModel* box, core::BoxModel* boxModel){
			drawBoxOuter(box, core::Color(0), core::Color(180));
			drawBoxInner(box, core::Color(0), core::Color(180));
		}
	};

	class DrawStyleable: public Drawable<core::Styleable<BoxModelType> > {
	public:
		virtual void drawBox(core::Styleable<BoxModelType>* box, core::BoxModel* boxModel) {
			drawBoxOuter(boxModel, box->getColor(), box->getBgColor());
			drawBoxInner(boxModel, box->getColor(), box->getBgColor());
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
			drawable.push_back(new DrawStyleable());
		}else{
			drawable.push_back(new DrawBoxModel());
		}

		//add addressable drawer
		if(core::is_base_of<core::Addressable<BoxModelType>, BoxModelType>::value) {
			drawable.push_back(new DrawAddressable());
		}
	}
	
	~DebugDrawer() {}

	void drawTree(BoxModelType* rootNode) {
		drawBox(rootNode);
		ofPushMatrix();
		ofTranslate(rootNode->contentPosition + rootNode->position);
		for(typename BoxModelType::ChildrenIterator it = rootNode->childrenBegin(); it < rootNode->childrenEnd(); it++) {
			drawTree(*it);
		}
		ofPopMatrix();
	}
	
	void drawBox(BoxModelType* box) {
		for(typename std::vector<DrawableBase*>::iterator it = drawable.begin();it<drawable.end();it++){
			(*it)->drawBox(box);
		}
	}

private:
	std::vector<DrawableBase*> drawable;
};

}

}

}

#endif // DEBUGDRAW_H
