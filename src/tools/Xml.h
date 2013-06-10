#ifndef XML_H
#define XML_H

#include "pugixml.hpp"
#include "core/Composite.h"
#include "tools/Instancer.h"

namespace boxModel {

namespace Xml {

class Xml {
public:
	Xml();
	~Xml();

	static core::Composite* loadXml(std::string path) {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(path.c_str());
		if(result.status != pugi::status_ok) {
			debug::error("could not load "+path);
			return NULL;
		}
		core::Composite* root = NULL;
		root = parseXmlNode(doc.first_child());

		return root;
	}
private:
	static core::Composite* parseXmlNode(pugi::xml_node node) {
		core::Composite* ret = tools::Instancer::createInstance(node.name());
		if(ret == NULL)
			return ret;
		//loop children
		for (pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it) {
			core::Composite* t = parseXmlNode(*it);
			/*
			if(t != NULL)
				ret->addChild(t);
			*/
		}

		//parse properties
		/*
		if(is_base_of<Serializable, BoxModelType>::value) {
			Serializable* serial = (Serializable*)ret;
			Serializable::ValueList values;
			for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
				values.set(attr.name(), attr.value());
			}
			serial->deserialize(values);
		}
		*/


		return ret;
	}
};

}

}

#endif // XML_H