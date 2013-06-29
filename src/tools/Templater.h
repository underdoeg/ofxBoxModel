#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "core/Component.h"
#include "Composite.h"

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
	core::Composite* loadContent(std::string path, std::string id);	
private:
	std::string templatePath;	
};

}

}

#endif // TEMPLATE_H
