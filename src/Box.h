#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "ofMain.h"

namespace ofx
{
namespace BoxModel
{

/*
class Box
{
public:

	typedef std::deque<Box*> List;

	Box();
	~Box();

	void debugDraw();

	virtual void draw() {};

	Box* getRootBox();
	Box* getParent();
	bool hasParent();

	Box* createChild();
	void add(Box* box);

	Properties props;

private:
	void setParent(Box* parent);
	void calculateSize();
	virtual void layout();

	void propertyChanged(Properties::Event& e);

	Point position;
	Point outerSize;
	Point size;
	Point contentSize;
	Point contentPosition;


	bool bParent;
	Box* parent;

	List children;
};
*/
}
}

#endif // BOXMODEL_H
