#ifndef OFXBOX_H
#define OFXBOX_H

#include "ofMain.h"

#include "core/Composite.h"
#include "components/Addressable.h"
#include "components/Box.h"
#include "components/Stack.h"
#include "components/BoxDefinition.h"
#include "components/Layouter.h"
#include "components/Style.h"

using namespace boxModel;
using namespace core;
using namespace components;


class ofxBox: public Composite, public Addressable, public Stack, public Box, public BoxDefinition, public Style
{
public:
	ofxBox()
	{
		addComponent<Box>(this);
		addComponent<BoxDefinition>(this);
		addComponent<Stack>(this);
		addComponent<Addressable>(this);
		addComponent<Layouter>(&layouter);
		addComponent<Style>(this);
	}
	~ofxBox()
	{
	}
	
	string test;
	Layouter layouter;
};

#endif // OFXBOX_H
