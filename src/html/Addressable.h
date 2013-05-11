#ifndef ADDRESSABLE_H
#define ADDRESSABLE_H

#include <string>
#include <vector>
#include <algorithm>
#include "core/Utils.h"
#include "core/TreeNode.h"

namespace ofx {

namespace boxModel {

namespace html {

template <class BoxModelType>
class Addressable {
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

	std::string getId(){
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

	void findByAddress(std::string path){
		//convert to traversable
		BoxModelType* rootNode = core::crtpSelfPtr<Addressable, BoxModelType>(this);
		for(typename BoxModelType::ChildrenIterator it = rootNode->childrenBegin(); it < rootNode->childrenEnd(); it++){

		}
	}

private:
	std::vector<std::string> classes;
	std::string id;
};

}

}

}

#endif // ADDRESSABLE_H
