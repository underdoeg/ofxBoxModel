#include "Splitter.h"

using namespace boxModel::core;
using namespace boxModel::components;
using namespace std;

void Splitter::setup()
{
}

void Splitter::onFlush()
{
}

void Splitter::registerSplit(Splitter* split)
{
	splits.push_back(split);
	curSplitStatus = true;
}

bool Splitter::requestSplit(float x, float y)
{
	cout << "REQUESTING A SPLIT" << endl;
	curSplitStatus = false;
	splitRequested(x, y);
	return curSplitStatus;
}

