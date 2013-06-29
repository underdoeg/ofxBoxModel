#include "Templater.h"
#include "Xml.h"
#include "debug/Print.h"
#include "Layouter.h"
#include "Linker.h"

using namespace boxModel::tools;
using namespace boxModel::core;
using namespace boxModel::components;

Templater::Templater() {
}

Templater::~Templater() {
}

void Templater::setTemplate(std::string path) {
	templatePath = path;
}

std::vector<Composite*> Templater::loadContent(std::string path, std::string id) {
	tempRet.clear();
	tempRet.push_back(loadContent(Xml::loadAsVector(path), id));
	std::reverse(tempRet.begin(), tempRet.end());
	return tempRet;
}

Composite* Templater::loadContent(std::vector<Composite*> elements, std::string id) {
	curId = id;
	Composite* ret = Xml::load(templatePath);
	std::vector<Composite*> loadIntoVec = ret->findByAddress<Composite>(id);
	if(loadIntoVec.size()>0) {
		curRoot = loadIntoVec[0];
		for(Composite* comp: elements){
			curRoot->addChild(comp);
		}
		
		if(curRoot->hasComponent<Linker>()) {
			Linker* linker = curRoot->getComponent<Linker>();
			while(linker->getLinkTo() != NULL) {
				linker = linker->getLinkTo();
			}
			lastLinker = linker;
			if(linker->components->hasComponent<Layouter>()) {
				Layouter* layouter = linker->components->getComponent<Layouter>();
				layouter->overflowed.connect<Templater, &Templater::onOverflow>(this);
			}
		}
	} else {
		debug::warning("templater: ID not found ("+id+")");
	}
	ret->flush();
	return ret;
}

void boxModel::tools::Templater::onOverflow(std::vector<core::ComponentContainer*> compList) {

	Stack* stack = lastLinker->components->getComponent<Stack>();
	for(ComponentContainer* comp: compList) {
		if(comp->hasComponent<Stack>())
			stack->removeChild(comp->getComponent<Stack>());
	}

	std::vector<Composite*> comps;
	for(ComponentContainer* comp: compList){
		comps.push_back(core::castTo<ComponentContainer, Composite>(comp));
	}
	tempRet.push_back(loadContent(comps, curId));
}
