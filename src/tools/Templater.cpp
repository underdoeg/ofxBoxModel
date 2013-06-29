#include "Templater.h"
#include "Xml.h"
#include "debug/Print.h"

using namespace boxModel::tools;
using namespace boxModel::core;
using namespace boxModel::components;

Templater::Templater()
{
}

Templater::~Templater()
{
}

void Templater::setTemplate(std::string path)
{
	templatePath = path;
}

Composite* Templater::loadContent(std::string path, std::string id)
{
	Composite* ret = Xml::load(templatePath);
	std::vector<Composite*> loadIntoVec = ret->findByAddress<Composite>(id);
	if(loadIntoVec.size()>0){
		boxModel::debug::notice("HI THERE");
		Composite* loadInto = loadIntoVec[0];
		Xml::loadInto(loadInto, path);
	}
	return ret;
}
