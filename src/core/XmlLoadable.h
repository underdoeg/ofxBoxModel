#ifndef XMLLOADABLE_H
#define XMLLOADABLE_H

#include "pugixml.hpp"
#include "Addressable.h"
#include "Utils.h"
#include "Instanceable.h"

namespace boxModel {

namespace core {

template <class BoxModelType>
class XmlLoadable: public Instanceable<BoxModelType> {
public:
	XmlLoadable() {
		if(!is_base_of<Addressable<BoxModelType>, BoxModelType>::value) {
			debug::error("to use the xml loader, you also need an Addressable");
			return;
		}
	};
	~XmlLoadable() {};
	
	static BoxModelType* loadXml(std::string path){
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(path.c_str());
		if(result.status != pugi::status_ok){
			debug::error("could not load "+path);
			return NULL;
		}
		BoxModelType* root = NULL;
		root = parseXmlNode(doc.first_child());
		
		return root;
	}
	
	void loadXmlInto(std::string path) {
		BoxModelType* box = loadXml(path);
		if(box != NULL)
			crtpSelfPtr<XmlLoadable, BoxModelType>(this)->addChild();
	}

	void registerXmlElement(std::string type) {

	}

	void saveAsXml(std::string path) {
		if(!is_base_of<Addressable<BoxModelType>, BoxModelType>::value || !is_base_of<Serializable, BoxModelType>::value) {
			debug::error("can only save addressable and serializable box types as XML");
			return;
		}
		pugi::xml_document doc;
		addToXmlNode(&doc);
		doc.save_file(path.c_str());
	}
private:
	static BoxModelType* parseXmlNode(pugi::xml_node node){
		BoxModelType* ret = Instanceable<BoxModelType>::createInstance(node.name());
		return ret;
	}

	void addToXmlNode(pugi::xml_node* parent) {
		BoxModelType* box = crtpSelfPtr<XmlLoadable, BoxModelType>(this);
		pugi::xml_node node = parent->append_child(((Addressable<BoxModelType>*)box)->getType().c_str());

		Serializable::ValueList values = ((Serializable*)box)->getSerialized();
		for(Serializable::ValueMap::iterator it = values.map.begin(); it != values.map.end(); it++) {
			pugi::xml_attribute attr = node.append_attribute((*it).first.c_str());
			attr.set_value((*it).second.value.c_str());
		}

		for(typename TreeNode<BoxModelType>::ChildrenIterator it = box->childrenBegin(); it<box->childrenEnd(); it++) {
			(*it)->addToXmlNode(&node);
		}
	}


};

}

}

#endif // XMLLOADABLE_H
