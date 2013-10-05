#include "InfoViewer.h"

namespace boxModel {
namespace debug {

InfoViewer::InfoViewer() {

}

InfoViewer::~InfoViewer() {
}

void InfoViewer::setComponentContainer(core::ComponentContainer* container) {
	for(unsigned int i=0; i < container->getNumComponents(); i++) {
		addInfoForComponent(container->getComponent(i));
	}
	flush();
}

void InfoViewer::addInfoForComponent(core::Component* component) {
	//check if something changed
	if(componentNames.find(component->getName()) == componentNames.end()) {
		boxes::H1* name = new boxes::H1(component->getName());
		componentNames[component->getName()] = name;
		addChild(name);
	}

	core::Component::Info info;
	component->getInfo(info);

	for(auto inf:info) {
		if(infoNames.find(inf.first) == infoNames.end()) {
			boxes::H2* infoName = new boxes::H2(inf.first);
			addChild(infoName);
			infoNames[inf.first] = infoName;

			boxes::TextBox* infoContent = new boxes::TextBox(inf.second);
			addChild(infoContent);
			infos[inf.first] = infoContent;
		}else{
			infos[inf.first]->text = inf.second;
		}
	}
}

string InfoViewer::getType() {
	return "infoViewer";
}

}
} //end namespace
