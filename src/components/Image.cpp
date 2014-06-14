#include "Image.h"

namespace boxModel {

namespace components {

Image::Image() {
	fitMode = ImageAutoHeight;
}

Image::~Image() {
}

std::string Image::getName() {
	return "Image";
}

void Image::setup() {
	LISTEN_FOR_COMPONENT(Css, Image, onCss)
	LISTEN_FOR_COMPONENT(Css, Image, onCss)
}

void Image::onBoxDefinition(BoxDefinition* boxDef) {
	boxDefinition = boxDef;
}

void Image::onCss(Css* c) {
	css = c;
}

}
}
