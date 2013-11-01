#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "boxes/Box.h" // Base class: boxModel::boxes::Box
#include "InfoViewer.h"
#include "components/Draggable.h"
#include "boxes/Texts.h"
#include "tools/BoxConstrainer.h"

namespace boxModel {

namespace debug {

class DebuggerPanel: public boxModel::boxes::Box, public boxModel::components::Draggable {
public:
	DebuggerPanel() {
		addComponent<components::Draggable>(this);
		title.text = "DEBUGGER";
		addChild(&title);
		curInfoViewer = NULL;
	}

	std::string getType() {
		return "debuggerPanel";
	}

	void showInfo(core::ComponentContainer* container){
		if(curInfoViewer != NULL)
			curInfoViewer->hide();

		if(infoViewers.find(container) == infoViewers.end())
			addChild(&infoViewers[container]);
		InfoViewer& iv = infoViewers[container];
		iv.setComponentContainer(container);
		curInfoViewer = &iv;
		infoViewers[container].show();
		flush();
	}

private:
	boxes::H1 title;

	std::map<core::ComponentContainer*, InfoViewer> infoViewers;
	InfoViewer* curInfoViewer;
};

class Debugger : public boxModel::boxes::Box {
public:
	Debugger();
	~Debugger();

	std::string getType();

	void setComponent(core::Component* component);
	void setComponentContainer(core::ComponentContainer* container);

private:

	void preDraw();

	void onMouseMove(float mouseX, float mouseY);
	void onMouseMoveOutside(float mouseX, float mouseY);
	void onMouseClick(float mouseX, float mouseY, int button);

	core::ComponentContainer* rootContainer;

	DebuggerPanel panel;
	boxModel::tools::BoxConstrainer* boxConstrainer;
};

}

}

#endif // DEBUGGER_H
