#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "core/Component.h"
#include "Composite.h"
#include "Linker.h"

namespace boxModel
{

namespace tools
{

class Templater
{
public:
	Templater();
	~Templater();
	void setTemplate(std::string path);
	std::vector<core::Composite*> loadContent(std::string path, std::string id);	
private:
	core::Composite* loadContent(std::vector<core::Composite*> elements, std::string id);
	
	void onOverflow(std::vector<core::ComponentContainer*> compList);
	void onLinkTo();
	std::string templatePath;	
	core::Composite* curRoot;
	components::Linker* lastLinker;
	std::vector<core::Composite*> tempRet;
	std::string curId;
};

}

}

#endif // TEMPLATE_H
