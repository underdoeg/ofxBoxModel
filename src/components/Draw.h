#ifndef DRAW_H
#define DRAW_H

#include "Component.h" // Base class: boxModel::core::Component
#include "components/Stack.h"
#include "components/Style.h"
#include "components/BoxModel.h"
#include "components/BoxDefinition.h"
#include "core/RendererBase.h"

namespace boxModel {

namespace components {

class Draw : public boxModel::core::Component {
public:
	Draw();
	~Draw();

	void setup();

	void draw();
	virtual void onDraw();
	std::string getName();
	static core::RendererBase* renderer;

	Nano::signal<void()> preDraw;
	Nano::signal<void(Draw*)> preDrawRef;

	Nano::signal<void()> postDraw;
	Nano::signal<void(Draw*)> postDrawRef;

protected:
	void drawDecorators();
private:

	void onStack(Stack* s);
	void onStyle(Style* s);
	void onBoxModel(BoxModel* bm);
	void onBoxDefinition(BoxDefinition* bd);

	Stack* stack;
	Style* style;
	BoxModel* boxModel;
	BoxDefinition* boxDefinition;

	bool bDrawDecorators;
};

}
}

#endif // DRAW_H
