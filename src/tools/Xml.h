#ifndef XML_H
#define XML_H

#include "pugixml.hpp"
#include "core/Composite.h"
#include "tools/Instancer.h"
#include "components/Stack.h"
#include "components/Serializer.h"

namespace boxModel {

namespace tools {

class Xml {
public:
	Xml();
	~Xml();

	template <class Type>
	static Type* load(std::string path) {
		return core::castTo<core::Composite, Type>(load(path));
	}

	static core::Composite* load(std::string path) {
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
			return NULL;

		//parse properties
		if(ret->hasComponent<components::Serializer>()) {
			components::Serializer* serial = ret->getComponent<components::Serializer>();
			core::VariantList values;
			for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
				values.set(attr.name(), attr.value());
			}
			values.set("text", node.child_value());
			serial->deserialize(values);
		}

		//loop children
		if(ret->hasComponent<components::Stack>()) {
			components::Stack* stack = ret->getComponent<components::Stack>();
			for (pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it) {
				if((*it).type() != pugi::node_pcdata) {
					core::Composite* t = parseXmlNode(*it);
					if(t != NULL && t->hasComponent<components::Stack>())
						stack->addChild(t->getComponent<components::Stack>());
				}
			}
		}
		
		return ret;
	}
};

}

}

#endif // XML_H
