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

	static void setRenderer(boxModel::core::RendererBase* renderer);
	static boxModel::core::RendererBase* getRenderer();
	
	void draw();
	void draw(bool drawChildren);
	std::string getName();

	Nano::signal<void()> preDraw;
	Nano::signal<void(Draw*)> preDrawRef;

	Nano::signal<void()> onDraw;
	Nano::signal<void(Draw*)> onDrawRef;

	Nano::signal<void()> postDraw;
	Nano::signal<void(Draw*)> postDrawRef;

protected:
	virtual void customDraw();
	void drawDecorators();

private:

	void onStack(Stack* s);
	void onStyle(Style* s);
	void onBoxModel(BoxModel* bm);
	void onBoxDefinition(BoxDefinition* bd);

	static core::RendererBase* renderer;

	Stack* stack;
	Style* style;
	BoxModel* boxModel;
	BoxDefinition* boxDefinition;

	bool bDrawDecorators;
};

}
}

#endif // DRAW_H
