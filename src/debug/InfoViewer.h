#ifndef INFOVIEWER_H
#define INFOVIEWER_H

#include "boxes/Box.h"
#include "boxes/Texts.h"

namespace boxModel {
namespace debug {

class InfoViewer: public boxModel::boxes::Box {
public:
	InfoViewer();
	~InfoViewer();

	void setComponentContainer(core::ComponentContainer* container);
	string getType();

private:
	void addInfoForComponent(core::Component* component);
	core::ComponentContainer* container;
};

}
}
#endif // INFOVIEWER_H
