#ifndef OFXBOX_H
#define OFXBOX_H

#include "ofMain.h"
#include "core/Component.h"
#include "components/Addressable.h"
#include "components/Box.h"
#include "components/Stack.h"
#include "components/BoxDefinition.h"
#include "components/Layouter.h"
#include "components/Style.h"
#include "components/Css.h"
#include "components/Serializer.h"
#include "components/Linker.h"
#include "components/Splitter.h"
#include "components/Mouse.h"

class ofxBox: 
	public boxModel::core::ComponentContainer, public boxModel::components::Addressable, public boxModel::components::Stack, 
	public boxModel::components::Box, public boxModel::components::BoxDefinition, public boxModel::components::Style, 
	public boxModel::components::Css, public boxModel::components::Serializer, public boxModel::components::Linker, 
	public boxModel::components::Splitter, public boxModel::components::Mouse
{
public:
	ofxBox()
	{
		addComponent<boxModel::components::Stack>(this);
		addComponent<boxModel::components::Addressable>(this);
		addComponent<boxModel::components::Box>(this);
		addComponent<boxModel::components::BoxDefinition>(this);
		addComponent<boxModel::components::Layouter>(&layouter);
		addComponent<boxModel::components::Style>(this);
		addComponent<boxModel::components::Css>(this);
		addComponent<boxModel::components::Serializer>(this);
		addComponent<boxModel::components::Linker>(this);
		addComponent<boxModel::components::Splitter>(this);
		addComponent<boxModel::components::Mouse>(this);
	}

	virtual ~ofxBox(){};

	virtual string getType(){
		return "box";
	}
	
	boxModel::components::Layouter layouter;
};

#endif // OFXBOX_H
