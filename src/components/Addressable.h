#ifndef ADDRESSABLE_H
#define ADDRESSABLE_H

#include "core/Utils.h"
#include "core/Component.h"
#include "Serializer.h"
#include "Stack.h"
#include <vector>
#include <string>
#include <algorithm>

namespace boxModel {

namespace components {

class Addressable: public core::Component {
public:

	void setup() {
		//assert(componentContainer->hasComponent<Stackable<Addressable>>());
		LISTEN_FOR_COMPONENT(Serializer, Addressable, onSerializer)
	}
	
	Addressable() {
		id = "";
	}

	bool isType(std::string Addressable) {
		return getType() == Addressable;
	}

	virtual std::string getType() {
		return "undefined";
	}

	std::vector<std::string> getClasses() {
		return classes;
	}

	void setId(std::string str) {
		str = core::stringTrim(str);
		if(str == id)
			return;
		/* //TODO: warn about duplicate IDs
		if(str.size() == 0) {
			if(id.size()>0)
				idsTaken.erase(std::remove(idsTaken.begin(), idsTaken.end(), str), idsTaken.end());
			return;
		}
		if(std::find(idsTaken.begin(), idsTaken.end(), str)!=idsTaken.end())
			debug::warning("duplicate ID: "+str);
		else
			idsTaken.push_back(str);
		*/
		id = str;
	}

	std::string getId() {
		return id;
	}

	bool isId(std::string idName) {
		return id == idName;
	}

	bool hasId() {
		return id != "";
	}

	bool hasClass(std::string className) {
		return (std::find(classes.begin(), classes.end(), className) != classes.end());
	}

	void addClass(std::string className) {
		classes.push_back(className);
	}
	
	void addClasses(std::vector<std::string> classNames){
		classes.insert(classes.end(), classNames.begin(), classNames.end());
	}

	void removeClass(std::string className) {
		classes.erase(std::remove(classes.begin(), classes.end(), className), classes.end());
	}
	
	template<class Type>
	std::vector<Type*> findByAddress(std::string path){
		std::vector<Type*> ret;
		std::vector<Addressable*> res = findByAddress(path);
		for(Addressable* item:res){
			if(core::instanceIsBaseOf<Addressable, Type>(item)){
				ret.push_back(core::castTo<Addressable, Type>(item, false));
			}
		}
		return ret;
	}
	
	std::vector<Addressable*> findByAddress(std::string path) {
		//prepare return vector
		std::vector<Addressable*> ret;
		
		//check for Stackable
		if(!components->hasComponent<Stack>()) {
			core::componentDependencyWarning("Addressable::findByAddress", "Stackable");
			return ret;
		}

		//split the string into address fragments
		std::vector<std::string> pathSplitted = core::stringSplit(path);
		

		//store temporary candidates for return
		std::vector<Addressable*> curRet;
		curRet.push_back(this);

		//go through the path
		for(std::vector<std::string>::iterator itPath = pathSplitted.begin(); itPath < pathSplitted.end(); itPath++) {
			std::string item = core::stringTrim(*itPath);

			std::vector<Addressable*> tmp;

			//check for class id or item
			if(item.size()>0) {
				char begin = item[0];
				switch(begin) {
				case '.':
					item.erase(0,1);
					for(Addressable* addr: curRet) {
						std::vector<Addressable*> t = findByClass(item, addr, (itPath != pathSplitted.begin()));
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
					break;
				
				case '#':
					item.erase(0,1);
					for(Addressable* addr: curRet) {
						std::vector<Addressable*> t = findById(item, addr, (itPath != pathSplitted.begin()));
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
					break;
				default:
					for(Addressable* addr: curRet) {
						std::vector<Addressable*> t = findByType(item, addr, (itPath != pathSplitted.begin()));
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
					break;
				}
			}
			//push current items into curRet;
			curRet = tmp;

			if(itPath == pathSplitted.end()-1)
				ret = curRet;
		}

		//remove duplicates
		sort( ret.begin(), ret.end() );
		ret.erase( unique( ret.begin(), ret.end() ), ret.end() );

		return ret;
	}

private:
	static std::vector<std::string > idsTaken;

	std::vector<Addressable*> findByClass(std::string className, Addressable* root, bool skipRoot = false) {
		std::vector<Addressable*> ret;
		if(!skipRoot && root->hasClass(className)) {
			ret.push_back(root);
		}
	
		Stack* stack = root->components->getComponent<Stack>();
	
		for(Stack* stackChild: stack->getChildren()){
			std::vector<Addressable*> v = findByClass(className, stackChild->components->getComponent<Addressable>());
			ret.insert( ret.end(), v.begin(), v.end() );
		}
		
		return ret;
	}
	
	std::vector<Addressable*> findById(std::string idName, Addressable* root, bool skipRoot = false) {
		std::vector<Addressable*> ret;
		if(!skipRoot && root->isId(idName)) {
			ret.push_back(root);
		}
	
		Stack* stack = root->components->getComponent<Stack>();
	
		for(Stack* stackChild: stack->getChildren()){
			std::vector<Addressable*> v = findById(idName, stackChild->components->getComponent<Addressable>());
			ret.insert( ret.end(), v.begin(), v.end() );
		}
		
		return ret;
	}
	
	std::vector<Addressable*> findByType(std::string typeName, Addressable* root, bool skipRoot = false) {
		std::vector<Addressable*> ret;
		if(!skipRoot && root->isType(typeName)) {
			ret.push_back(root);
		}
	
		Stack* stack = root->components->getComponent<Stack>();
	
		for(Stack* stackChild: stack->getChildren()){
			std::vector<Addressable*> v = findByType(typeName, stackChild->components->getComponent<Addressable>());
			ret.insert( ret.end(), v.begin(), v.end() );
		}
		
		return ret;
	}
	
	/************************** SERIALIZING ***********************************************/
		
	void onSerializer(Serializer* ser){
		ser->deserialized.connect<Addressable, &Addressable::onDeserialize>(this);
		ser->serialized.connect<Addressable, &Addressable::onSerialize>(this);
	}
	
	void onSerialize(core::VariantList& variants){
		if(hasId())
			variants.set("id", getId());
		if(classes.size()>0)
			variants.set("class", core::Variant(classes));
	}
	
	void onDeserialize(core::VariantList& variants){
		if(variants.hasKey("class")){
			addClasses(variants.get("class").asStringList());
		}
		if(variants.hasKey("id")){
			setId(variants.get("id"));
		}
	}

	std::vector<std::string> classes;
	std::string id;
};

}

}

#endif // ADDRESSABLE_H
