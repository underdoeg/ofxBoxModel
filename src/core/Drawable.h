#ifndef DRAWABLE_H
#define DRAWABLE_H

namespace boxModel
{

namespace core
{

template <class BoxModelType>
class Drawable
{
public:
	Drawable(){};
	~Drawable(){};
	
	void draw(){
		pushMatrix();
		BoxModelType* t = crtpSelfPtr<Layoutable, BoxModelType>(this);
		translateMatrix(t->contentPosition.x, t->contentPosition.y);
		onDraw();
		for(typename core::TreeNode<BoxModelType>::ChildrenIterator it = t->childrenBegin(); it < t->childrenEnd(); it++) {
				(*it)->draw();
		}
		popMatrix();
	}
	
	virtual void onDraw() = 0;
	virtual void pushMatrix() = 0;
	virtual void translateMatrix(float x, float y) = 0;
	virtual void popMatrix() = 0;
};

}

}

#endif // DRAWABLE_H
