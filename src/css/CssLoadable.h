#ifndef CSSLOADABLE_H
#define CSSLOADABLE_H

#include "core/BoxModel.h"
#include "debug/Print.h"
#include <regex.h>

namespace ofx {

namespace boxModel {

namespace css {


template <class BoxModelType>
class CssLoadable {
public:
	CssLoadable() {};
	~CssLoadable() {};

	void loadCss(std::string path) {
		ofBuffer buffer = ofBufferFromFile(path);
		setCss(buffer.getText());
	}

	void setCss(std::string cssDefinition) {
		//std::vector<string>
		//use slre https://code.google.com/p/slre/source/checkout ?
	}
};

}

}

}

#endif // CSSLOADABLE_H
