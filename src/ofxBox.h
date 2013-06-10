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
#include "components/Css.h"
#include "components/Serializer.h"

using namespace boxModel::core;
using namespace boxModel::components;


class ofxBox: public Composite, public Addressable, public Stack, public Box, public BoxDefinition, public Style, public Css, public Serializer
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
		addComponent<Css>(this);
		addComponent<Serializer>(this);
		//Instancer::addInstancer<ofxBox>(getType());
	}
	
	~ofxBox()
	{
	}
	
	string getType(){
		return "box";
	}
	
	Layouter layouter;
};

#endif // OFXBOX_H
