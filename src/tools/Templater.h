#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "core/Component.h"
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
	std::vector<core::ComponentContainer*> loadContent(std::string path, std::string id);	
	
	template <class Type>
	std::vector<Type*> loadContent(std::string path, std::string id){
		std::vector<Type*> ret;
		std::vector<core::ComponentContainer*> comps = loadContent(path, id);
		for(core::ComponentContainer* comp: comps){
			Type* t = core::castTo<core::ComponentContainer, Type>(comp);
			if(t != NULL){
				ret.push_back(t);
			}
		}
		return ret;
	}
	
private:
	core::ComponentContainer* loadContent(std::vector<core::ComponentContainer*> elements, std::string id);
	
	void onOverflow(std::vector<core::ComponentContainer*> compList);
	void onLinkTo();
	std::string templatePath;	
	core::ComponentContainer* curRoot;
	components::Linker* lastLinker;
	std::vector<core::ComponentContainer*> tempRet;
	std::string curId;
};

}

}

#endif // TEMPLATE_H
