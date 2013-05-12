#ifndef ADDRESSABLE_H
#define ADDRESSABLE_H

#include <string>
#include <vector>
#include <algorithm>
#include "core/Utils.h"
#include "core/TreeNode.h"

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
		for(std::vector<std::string>::iterator it = pathSplitted.begin(); it < pathSplitted.end(); it++) {

			std::string item = trimString(*it);

			std::vector<BoxModelType*> tmp;

			//check for class id or item
			if(item.size()>0) {
				char begin = item[0];
				switch(begin) {
				case '.':
					item.erase(0,1);
					for(typename std::vector<BoxModelType*>::iterator it = curRet.begin(); it < curRet.end(); it++) {
						std::vector<BoxModelType*> t = findByClass(item, *it);
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
					break;
				case ',':

					break;
				default:

					break;
				}
			}
			//push current items into curRet;
			curRet = tmp;


			if(it == pathSplitted.end()-1)
				ret = curRet;
		}

		return ret;
	}

private:


	std::vector<BoxModelType*> findByClass(string className, BoxModelType* root) {
		std::vector<BoxModelType*> ret;
		if(root->hasClass(className)) {
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

}

}

}

#endif // ADDRESSABLE_H
