#ifndef INFOVIEWER_H
#define INFOVIEWER_H

#include "boxes/Box.h"
namespace boxModel {
namespace debug {

class InfoViewer: public boxes::Box {
public:
	InfoViewer();
	~InfoViewer();

	void setComponentContainer(core::ComponentContainer* container);
	string getType();
	
private:
	core::ComponentContainer* container;
};

}
}
#endif // INFOVIEWER_H
