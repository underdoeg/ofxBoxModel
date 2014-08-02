#ifndef SPLITTER_H
#define SPLITTER_H

#include "Component.h" // Base class: boxModel::core::Component
#include "BaseTypes.h"
#include "BoxModel.h"


namespace boxModel
{

namespace components
{

class Splitter : public boxModel::core::Component
{
public:

	std::string getName();
	
	void setup();
	
	void onFlush();
	
	Nano::Signal<void(float x, float y)> splitRequested;
	bool requestSplit(float x, float y);
	
	void merge();
	void getInfo(core::Component::Info& info);

	std::vector<core::ComponentContainer*> makeSplit();
	std::vector<core::ComponentContainer*> getSplits();
	
	core::Value<bool> hasSplits;
	core::Value<bool> isSplit;

private:
	void markAsSplit(Splitter* splitter);
	void onBoxDefinition(BoxModel* boxDefinition);
	void onBox(BoxDefinition* box);
	void onStack(Stack* stack);
	
	std::vector<core::ComponentContainer*> splits;
	core::Point splitPosition;
	
	core::Unit originalWidth;
	core::Unit originalHeight;
	BoxModel* boxDefinition;
	BoxDefinition* box;
	Stack* stack;
	Splitter* splitter;
	bool isSplitable;
};

}

}

#endif // SPLITTER_H
