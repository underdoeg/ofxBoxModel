#ifndef ADDRESSABLE_H
#define ADDRESSABLE_H

#include <string>
#include <vector>
#include <algorithm>
#include "core/Utils.h"
#include "core/TreeNode.h"
#include "debug/Print.h"

namespace ofx
{

namespace boxModel
{

namespace core
{

template <class BoxModelType>
class Addressable
{
public:
	Addressable() {
		id = "";
	}

	virtual std::string getType() {
		return "div";
	}

	std::vector<std::string> getClasses() {
		return classes;
	}

	void setId(std::string str) {
		str = trimString(str);
		if(str == id)
			return;
		if(str.size() == 0){
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

	std::vector<BoxModelType*> findByAddress(std::string path) {
		//TODO split by , first or should this be in css? yes! css
		BoxModelType* rootNode = core::crtpSelfPtr<Addressable, BoxModelType>(this);

		//split the string into address fragments
		std::vector<std::string> pathSplitted = splitString(path);

		std::vector<BoxModelType*> ret;

		//store temporary candidates for return
		std::vector<BoxModelType*> curRet;
		curRet.push_back(rootNode);

		//go through the path
		for(std::vector<std::string>::iterator itPath = pathSplitted.begin(); itPath < pathSplitted.end(); itPath++) {

			std::string item = trimString(*itPath);

			std::vector<BoxModelType*> tmp;

			//check for class id or item
			if(item.size()>0) {
				char begin = item[0];
				switch(begin) {
				case '.':
					item.erase(0,1);
					for(typename std::vector<BoxModelType*>::iterator it = curRet.begin(); it < curRet.end(); it++) {
						std::vector<BoxModelType*> t = findByClass(item, *it, (itPath != pathSplitted.begin()));
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
					break;
				case '#':
					item.erase(0,1);
					for(typename std::vector<BoxModelType*>::iterator it = curRet.begin(); it < curRet.end(); it++) {
						std::vector<BoxModelType*> t = findByClass(item, *it, (itPath != pathSplitted.begin()));
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
					break;
				default:

					break;
				}
			}
			//push current items into curRet;
			curRet = tmp;

			if(itPath == pathSplitted.end()-1)
				ret = curRet;
		}

		//remove duplicates. TODO: is there a way to avoid them? would it actually be faster? Also is the sort order of the vectors relevant? Random now...
		sort( ret.begin(), ret.end() );
		ret.erase( unique( ret.begin(), ret.end() ), ret.end() );

		return ret;
	}

private:
	static std::vector<std::string > idsTaken;

	std::vector<BoxModelType*> findByClass(string className, BoxModelType* root, bool skipRoot = false) {
		std::vector<BoxModelType*> ret;
		if(!skipRoot && root->hasClass(className)) {
			ret.push_back(root);
		}
		for(typename BoxModelType::ChildrenIterator it = root->childrenBegin(); it < root->childrenEnd(); it++) {
			std::vector<BoxModelType*> v = findByClass(className, *it);
			ret.insert( ret.end(), v.begin(), v.end() );
		}
		return ret;
	}

	std::vector<std::string> classes;
	std::string id;
};

template<class BoxModelType>  std::vector<std::string > Addressable<BoxModelType>::idsTaken;

}

}

}

#endif // ADDRESSABLE_H
