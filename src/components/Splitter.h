#ifndef SPLITTER_H
#define SPLITTER_H

#include "Component.h" // Base class: boxModel::core::Component

namespace boxModel
{

namespace components
{

class Splitter : public boxModel::core::Component
{
	virtual void onFlush();
	virtual void setup();
	
	Nano::signal<void(float x, float y)> splitRequested;
	bool requestSplit(float x, float y);
	
	void registerSplit(Splitter* split);
	
private:
	bool curSplitStatus;
	std::vector<Splitter*> splits;
};

}

}

#endif // SPLITTER_H
