#ifndef HEADINGS_H
#define HEADINGS_H

#include "boxes/Box.h"
#include "components/Text.h"

namespace boxModel {
namespace boxes {

class TextBox: public Box, public components::Text {
public:
	TextBox(std::string t = "") {
		addComponent<Text>(this);
		text = t;
	}

	virtual string getType() {
		return "p";
	}
};

class H1: public TextBox {
public:
	H1(std::string t = ""):TextBox(t) {

	}
	virtual string getType() {
		return "h1";
	}
};

class H2: public TextBox {
public:
	H2(std::string t = ""):TextBox(t) {

	}
	virtual string getType() {
		return "h2";
	}
};

class H3: public TextBox {
public:
	H3(std::string t = ""):TextBox(t) {

	}
	virtual string getType() {
		return "h3";
	}
};

}
}

#endif // HEADINGS_H
