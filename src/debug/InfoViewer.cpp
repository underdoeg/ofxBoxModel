#include "InfoViewer.h"

namespace boxModel{
namespace debug{
	
InfoViewer::InfoViewer()
{
	
}

InfoViewer::~InfoViewer()
{
}

void InfoViewer::setComponentContainer(core::ComponentContainer* container)
{
	for(unsigned int i=0; i < container->getNumComponents(); i++){
		addInfoForComponent(container->getComponent(i));
	}
	flush();
}

void InfoViewer::addInfoForComponent(core::Component* component)
{
	boxes::H1* name = new boxes::H1(component->getName());
	addChild(name);
	
	core::Component::Info info;
	component->getInfo(info);
	
	for(auto inf:info){
		boxes::H2* infoName = new boxes::H2(inf.first);
		addChild(infoName);
		boxes::TextBox* infoContent = new boxes::TextBox(inf.second);
		addChild(infoContent);
	}
}

string InfoViewer::getType()
{
	return "infoViewer";
}

}} //end namespace
