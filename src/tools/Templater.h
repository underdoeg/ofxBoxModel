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
	
	template <class Type>
	std::vector<Type*> loadContent(std::string path, std::string id){
		std::vector<Type*> ret;
		std::vector<core::Composite*> comps = loadContent(path, id);
		for(core::Composite* comp: comps){
			Type* t = core::castTo<core::Composite, Type>(comp);
			if(t != NULL){
				ret.push_back(t);
			}
		}
		return ret;
	}
	
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
