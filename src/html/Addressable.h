#ifndef ADDRESSABLE_H
#define ADDRESSABLE_H

#include <string>
#include <vector>
#include <algorithm>

namespace ofx {

namespace boxModel {

namespace html {

template <class BoxModelType>
class Addressable {
public:
	virtual std::string getType() {
		return "div";
	}

	std::vector<std::string> getClasses() {
		return classes;
	}

	bool hasClass() {
		if(std::find(classes.begin(), classes.end(), x) != classes.end()) {

		} else {

		}
	}

	void addClass(std::string className) {
		classes.push_back(className);
	}

	void removeClass(std::string className) {
		classes.erase(std::remove(classes.begin(), classes.end(), className), classes.end());
	}

private:
	std::vector<std::string> classes;
};

}

}

}

#endif // ADDRESSABLE_H
