#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "boxes/Box.h" // Base class: boxModel::boxes::Box
#include "InfoViewer.h"
#include "components/Draggable.h"
#include "boxes/Texts.h"
#include "tools/BoxConstrainer.h"

namespace boxModel {

namespace debug {

class DebuggerOverlay: public boxModel::boxes::Box{
public:
	DebuggerOverlay(){
		setMouseIgnore(true);
		setBoxDefinitionUpdate(false);
		positioning = components::Position::Absolute;
		layouter.setLayoutable(false);
	}

	std::string getType() {
		return "debuggerOverlay";
	}

	tools::BoxConstrainer boxConstrainer;
};

class DebuggerOverlayCurrent: public boxModel::boxes::Box{
public:
	DebuggerOverlayCurrent(){
		setMouseIgnore(true);
		setBoxDefinitionUpdate(false);
		positioning = components::Position::Absolute;
		layouter.setLayoutable(false);
	}

	std::string getType() {
		return "debuggerOverlayCurrent";
	}

	tools::BoxConstrainer boxConstrainer;
};

class DebuggerPanel: public boxModel::boxes::Box, public boxModel::components::Draggable {
public:
	DebuggerPanel() {
		addComponent<components::Draggable>(this);
		title.text = "DEBUGGER";
		help.margin.top = 10;
		help.text = "click on element for info";
		addChild(&title);
		addChild(&help);
		curInfoViewer = NULL;
	}

	std::string getType() {
		return "debuggerPanel";
	}

	void showInfo(core::ComponentContainer* container){
		if(help.isVisible())
			help.hide();

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
	boxes::TextBox help;

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
	void onMouseMove(float mouseX, float mouseY);
	void onMouseMoveOutside(float mouseX, float mouseY);
	void onMouseClick(float mouseX, float mouseY, int button);

	core::ComponentContainer* rootContainer;
	components::Stack* rootStack;

	DebuggerPanel panel;
	DebuggerOverlay overlay;
	DebuggerOverlayCurrent overlayCurrent;
	boxModel::tools::BoxConstrainer boxConstrainer;
};

}

}

#endif // DEBUGGER_H
