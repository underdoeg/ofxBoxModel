#ifndef CSSLOADABLE_H
#define CSSLOADABLE_H

#include "core/BoxModel.h"
#include "debug/Print.h"

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
		
	}
};

}

}

}

#endif // CSSLOADABLE_H
