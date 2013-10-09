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

	std::map<std::string, boxes::H2*> componentNames;
	std::map<std::string, boxes::H3*> infoNames;
	std::map<std::string, boxes::TextBox*> infos;

};

}
}
#endif // INFOVIEWER_H
