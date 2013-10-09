#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "boxes/Box.h" // Base class: boxModel::boxes::Box
#include "InfoViewer.h"
#include "components/Draggable.h"

namespace boxModel
{

namespace debug
{

class Debugger : public boxModel::boxes::Box, public boxModel::components::Draggable
{
public:
	Debugger();
	~Debugger();

	std::string getType();

	void setComponent(core::Component* component);
	void setComponentContainer(core::ComponentContainer* container);

private:
	void onComponentClick(int button, components::Mouse* mouse);

	core::ComponentContainer* rootContainer;
	std::map<core::ComponentContainer*, InfoViewer> infoViewers;
	InfoViewer* curInfoViewer;
};

}

}

#endif // DEBUGGER_H
