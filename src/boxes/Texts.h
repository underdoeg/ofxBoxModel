#ifndef HEADINGS_H
#define HEADINGS_H

#include "boxes/Box.h"
#include "components/Text.h"

namespace boxModel {
namespace boxes {

class TextBox: public Box, public components::Text {
public:
	TextBox() {
		addComponent<Text>(this);
	}

	virtual string getType() {
		return "p";
	}
};

class H1: public TextBox {
	virtual string getType() {
		return "h1";
	}
};

class H2: public TextBox {
	virtual string getType() {
		return "h2";
	}
};

class H3: public TextBox {
	virtual string getType() {
		return "h3";
	}
};

}
}

#endif // HEADINGS_H
