#ifndef XML_H
#define XML_H

#include "pugixml.hpp"
#include "tools/Instancer.h"
#include "components/Stack.h"
#include "components/Serializer.h"
#include "core/Globals.h"

namespace boxModel {

namespace tools {

class Xml {
public:
	Xml();
	~Xml();

	template <class Type>
	static Type* load(std::string path) {
		return core::castTo<core::ComponentContainer, Type>(load(path));
	}
	
	static string getXMLString(std::string path){
		path = core::Globals::get().dataRoot+path;
		std::ifstream t(path);
		std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
		str = core::stringReplace(str, "<br/>", "\n");
		str = core::stringReplace(str, "<br />", "\n");
		str = core::stringReplace(str, "<br>", "\n");
		return str;
	}
	
	static core::ComponentContainer* load(std::string path) {
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load(getXMLString(path).c_str());
		if(result.status != pugi::status_ok) {
			debug::error("could not load "+path);
			return NULL;
		}
		core::ComponentContainer* root = NULL;
		root = parseXmlNode(doc.first_child());
		
		return root;
	}
	
	static std::vector<core::ComponentContainer*> loadAsVector(std::string path){
		std::vector<core::ComponentContainer*> ret;
		pugi::xml_document doc;
		
		//pugi::xml_parse_result result = doc.load_file(path.c_str());
		pugi::xml_parse_result result = doc.load(getXMLString(path).c_str());
		
		if(result.status != pugi::status_ok) {
			debug::error("could not load "+path);
			return ret;
		}
		
		for (pugi::xml_node_iterator it = doc.begin(); it != doc.end(); ++it) {
			core::ComponentContainer* child = parseXmlNode(*it);
			ret.push_back(child);
		}
		return ret;
	}

	static void loadInto(core::ComponentContainer* root, std::string path) {
		std::vector<core::ComponentContainer*> composites = loadAsVector(path);
		
		boxModel::components::Stack* rootStack = root->getComponent<boxModel::components::Stack>();
		for (core::ComponentContainer* comp: composites) {
			if(comp->hasComponent<components::Stack>()) {
				rootStack->addChildContainer(comp);
			}
		}
	}

private:
	static core::ComponentContainer* parseXmlNode(pugi::xml_node node) {
		core::ComponentContainer* ret = tools::Instancer::createInstance(node.name());
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
					core::ComponentContainer* t = parseXmlNode(*it);
					if(t != NULL && t->hasComponent<components::Stack>())
						stack->addChild(t->getComponent<components::Stack>());
				}
			}
		}
		
		ret->onLoadComplete();
		
		return ret;
	}
};

}

}

#endif // XML_H
