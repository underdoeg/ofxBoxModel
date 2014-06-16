#include "Box.h"

namespace boxModel {
namespace boxes {

ImageBox::ImageBox() {
	addComponent<boxModel::components::Image>(this);
}
	
ImageBox::~ImageBox() {
}

std::string ImageBox::getType() {
	return "img";
}

}} //end namespace
