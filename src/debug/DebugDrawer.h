#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "core/BoxModel.h"
#include "core/TreeNode.h"

namespace ofx
{

namespace boxModel
{

namespace debug
{

template <class TreeNodeType>
class DebugDrawer
{
			public:
	DebugDrawer(){}
	~DebugDrawer(){}

	void drawTree(TreeNodeType* rootNode){
		for(int i=0;i<rootNode->getNumChildren();i++){
			drawTree(rootNode->getChild(i));
		}
	}
	
	void drawBox(TreeNodeType* box) {
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


};

}

}

}

#endif // DEBUGDRAW_H
