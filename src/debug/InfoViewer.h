#ifndef INFOVIEWER_H
#define INFOVIEWER_H

#include "ofxBox.h"

namespace boxModel {
namespace debug {

class InfoViewer: public ofxBox {
public:
	InfoViewer();
	~InfoViewer();

	void setComponentContainer(core::ComponentContainer* container);
	
private:
	core::ComponentContainer* container;
};

}
}
#endif // INFOVIEWER_H
