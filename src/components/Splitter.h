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
	void onFlush();
	void setup();
	
	Nano::signal<void(float x, float y)> splitRequested;
	bool requestSplit(float x, float y);
	
	void merge();
	
	std::vector<core::ComponentContainer*> makeSplit();
	std::vector<core::ComponentContainer*> getSplit();
	
	core::Value<bool> hasSplits;
	core::Value<bool> isSplit;

private:
	void markAsSplit(Splitter* splitter);
	void onBoxDefinition(BoxDefinition* boxDefinition);
	void onBox(Box* box);
	void onStack(Stack* stack);
	
	std::vector<core::ComponentContainer*> splits;
	core::Point splitPosition;
	
	core::Unit originalWidth;
	core::Unit originalHeight;
	BoxDefinition* boxDefinition;
	Box* box;
	Stack* stack;
	Splitter* splitter;
};

}

}

#endif // SPLITTER_H
