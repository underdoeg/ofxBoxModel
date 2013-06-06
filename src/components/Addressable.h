#ifndef ADDRESSABLE_H
#define ADDRESSABLE_H

#include "core/Utils.h"
#include "core/Component.h"
#include "Stackable.h"
#include <vector>

namespace boxModel {

namespace components {

template<class Type>
class Addressable: public core::Component, private core::TypedComponent<Addressable<Type>, Type>{
public:
	//COMPONENT()
	
	void setup(){
		assert(componentContainer->hasComponent<Stackable<Type>>());
	}
	
	Addressable() {
		id = "";
	}
	
	bool isTypeOf(std::string type){
		return getType() == type;
	}
	
	virtual std::string getType() {
		return "div";
	}

	std::vector<std::string> getClasses() {
		return classes;
	}

	void setId(std::string str) {
		str = core::stringTrim(str);
		if(str == id)
			return;
		if(str.size() == 0) {
			if(id.size()>0)
				idsTaken.erase(std::remove(idsTaken.begin(), idsTaken.end(), str), idsTaken.end());
			return;
		}
		if(std::find(idsTaken.begin(), idsTaken.end(), str)!=idsTaken.end())
			debug::warning("duplicate ID: "+str);
		else
			idsTaken.push_back(str);
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

	void removeClass(std::string className) {
		classes.erase(std::remove(classes.begin(), classes.end(), className), classes.end());
	}

	std::vector<Type*> findByAddress(std::string path) {

		//split the string into address fragments
		std::vector<std::string> pathSplitted = core::stringSplit(path);

		std::vector<Addressable<Type>*> ret;

		//store temporary candidates for return
		std::vector<Stackable<Type>*> curRet;
		curRet.push_back(this->getAsType());

		//go through the path
		for(std::vector<std::string>::iterator itPath = pathSplitted.begin(); itPath < pathSplitted.end(); itPath++) {

			std::string item = core::stringTrim(*itPath);

			std::vector<Type*> tmp;

			//check for class id or item
			if(item.size()>0) {
				char begin = item[0];
				switch(begin) {
				case '.':
					item.erase(0,1);
					for(typename std::vector<Type*>::iterator it = curRet.begin(); it < curRet.end(); it++) {
						std::vector<Type*> t = findByClass(item, *it, (itPath != pathSplitted.begin()));
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
					break;
				/*
				case '#':
					item.erase(0,1);
					for(typename std::vector<Type*>::iterator it = curRet.begin(); it < curRet.end(); it++) {
						std::vector<Type*> t = findById(item, *it, (itPath != pathSplitted.begin()));
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
					break;
				default:
					for(typename std::vector<Type*>::iterator it = curRet.begin(); it < curRet.end(); it++) {
						std::vector<Type*> t = findByType(item, *it, (itPath != pathSplitted.begin()));
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
					break;
				*/
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

	std::vector<Type*> findByClass(string className, Type* root, bool skipRoot = false) {
		std::vector<Type*> ret;
		if(!skipRoot && root->hasClass(className)) {
			ret.push_back(root);
		}
		for(typename Type::ChildrenIterator it = root->childrenBegin(); it < root->childrenEnd(); it++) {
			std::vector<Type*> v = findByClass(className, *it);
			ret.insert( ret.end(), v.begin(), v.end() );
		}
		return ret;
	}
	
	std::vector<Type*> findById(string idName, Type* root, bool skipRoot = false) {
		std::vector<Type*> ret;
		if(!skipRoot && root->isId(idName)) {
			ret.push_back(root);
		}
		for(typename Type::ChildrenIterator it = root->childrenBegin(); it < root->childrenEnd(); it++) {
			std::vector<Type*> v = findById(idName, *it);
			ret.insert( ret.end(), v.begin(), v.end() );
		}
		return ret;
	}
	
	
	std::vector<Type*> findByType(string type, Type* root, bool skipRoot = false) {
		std::vector<Type*> ret;
		if(!skipRoot && root->isTypeOf(type)) {
			ret.push_back(root);
		}
		for(typename Type::ChildrenIterator it = root->childrenBegin(); it < root->childrenEnd(); it++) {
			std::vector<Type*> v = findByType(type, *it);
			ret.insert( ret.end(), v.begin(), v.end() );
		}
		return ret;
	}

	std::vector<std::string> classes;
	std::string id;
};

template<class Type>  
std::vector<std::string > Addressable<Type>::idsTaken;

}

}

#endif // ADDRESSABLE_H
