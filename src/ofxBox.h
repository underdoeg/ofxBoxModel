#ifndef OFXBOX_H
#define OFXBOX_H

#include "core/Composite.h"
#include "components/Addressable.h"
#include "components/BoxModel.h"
#include "components/Stackable.h"

using namespace boxModel;
using namespace core;
using namespace components;

class ofxBox: public Composite<ofxBox>, public BoxModel<ofxBox>, public Addressable<ofxBox>
{
public:
	ofxBox()
	{
		registerComponents<BoxModel<ofxBox>, Addressable<ofxBox> >(*this, *this);
	}
	~ofxBox()
	{
	}

};

#endif // OFXBOX_H
