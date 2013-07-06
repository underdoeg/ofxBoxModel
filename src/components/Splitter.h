#ifndef SPLITTER_H
#define SPLITTER_H

#include "Component.h" // Base class: boxModel::core::Component
#include "BaseTypes.h"
#include "BoxDefinition.h"

namespace boxModel
{

namespace components
{

class Splitter : public boxModel::core::Component
{
public:
	virtual void onFlush();
	virtual void setup();
	
	Nano::signal<void(float x, float y)> splitRequested;
	bool requestSplit(float x, float y);
	
	core::ComponentContainer* makeSplit();
	core::ComponentContainer* getSplit();
	
private:
	void onBoxDefinition(BoxDefinition* boxDefinition);
	void onBox(Box* box);
	
	core::ComponentContainer* split;
	core::Point splitPosition;
	bool curSplitStatus;
	core::Unit originalWidth;
	core::Unit originalHeight;
	BoxDefinition* boxDefinition;
	Box* box;
};

}

}

#endif // SPLITTER_H
