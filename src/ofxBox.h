#ifndef OFXBOX_H
#define OFXBOX_H

#include "ofMain.h"

#include "core/Composite.h"
#include "components/Addressable.h"
#include "components/Box.h"
#include "components/Stackable.h"
#include "components/BoxDefinition.h"

using namespace boxModel;
using namespace core;
using namespace components;


class ofxBox: public Composite, public Addressable, public Stackable, public Box, public BoxDefinition
{
public:
	ofxBox()
	{	
		addComponent<Box>(this);
		addComponent<BoxDefinition>(this);
		addComponent<Stackable>(this);
		addComponent<Addressable>(this);
	}
	~ofxBox()
	{
	}
	
	string test;
	
};

#endif // OFXBOX_H
