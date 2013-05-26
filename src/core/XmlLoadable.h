#ifndef XMLLOADABLE_H
#define XMLLOADABLE_H

#include "pugixml.hpp"

namespace boxModel
{

namespace core
{

template <class BoxModelType>
class XmlLoadable
{
public:
	XmlLoadable(){};
	~XmlLoadable(){};
	void loadXml(std::string path){
		
	}
	
	void registerXmlElement(std::string type){
		
	}
private:
	
};
 
}

}

#endif // XMLLOADABLE_H
