#ifndef OFXBOX_H
#define OFXBOX_H

#include "core/BoxModel.h"
#include "core/TreeNode.h"
#include "core/Addressable.h"
#include "core/Styleable.h"
#include "core/Layoutable.h"
#include "core/CssLoadable.h"
#include "core/Drawable.h"
#include "core/XmlLoadable.h"
#include "core/Serializable.h"
#include "debug/DebugDrawer.h"


using namespace boxModel::core;

class ofxBox: 
	public BoxModel, public TreeNode<ofxBox>, public Addressable<ofxBox>, 
	public Styleable<ofxBox>, public Layoutable<ofxBox>, 
	public boxModel::core::Drawable<ofxBox>, public boxModel::core::XmlLoadable<ofxBox>,
	public boxModel::core::Serializable, public CssLoadable<ofxBox>
{
public:
	typedef boxModel::debug::DebugDrawer<ofxBox> DebugDrawer;
	
	ofxBox();
	~ofxBox();

	virtual std::string getType();

	virtual void onDraw() {};

	void pushMatrix();
	void translateMatrix(float x, float y);
	void popMatrix();
};

#endif // OFXBOX_H
