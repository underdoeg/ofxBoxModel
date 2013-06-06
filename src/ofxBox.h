#ifndef OFXBOX_H
#define OFXBOX_H

#include "core/Composite.h"
#include "components/Addressable.h"
#include "components/BoxModel.h"
#include "components/Stackable.h"

using namespace boxModel;
using namespace core;
using namespace components;


class ofxBox: private Composite, public Stackable<ofxBox>, public BoxModel, public Addressable<ofxBox>
{
public:
	ofxBox()
	{
		addComponent<BoxModel>(this);
		addComponent<Stackable<ofxBox>>(this);
		addComponent<Addressable<ofxBox>>(this);
		
		setupComponents();
	}
	~ofxBox()
	{
	}

};

#endif // OFXBOX_H
