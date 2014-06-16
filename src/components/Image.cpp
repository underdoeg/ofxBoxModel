#include "Image.h"
#include "Globals.h"

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
	LISTEN_FOR_COMPONENT(BoxDefinition, Image, onBoxDefinition);
	LISTEN_FOR_COMPONENT(BoxModel, Image, onBoxModel);
	LISTEN_FOR_COMPONENT(Draw, Image, onDraw);
	LISTEN_FOR_COMPONENT(Serializer, Image, onSerializer);
}

void Image::drawIt() {
	if(!isImageLoaded)
		return;
	img.draw(0, 0, drawSize.x, drawSize.y);
}

void Image::recalculateBoxSize() {
	/*
	if(!isImageLoaded)
		return;

	core::Point p(imageWidth, imageHeight);
	bool setSize;
	if(boxModel) {
		if(boxModel->width == core::Unit::Auto && boxModel->height == core::Unit::Auto) {
			p.x = imageHeight;
			p.y = imageWidth;
		}
	}
	if(boxDefinition) {

	} else {
		drawSize.x = img.width;
		drawSize.y = img.height;
	}
	*/
}

void Image::onAutoHeight(float& height) {
	if(!isImageLoaded)
		return;
	
	if(boxModel->width == core::Unit::Auto){
		height = imageHeight;
	}else{
		if(boxDefinition)
			height =  boxDefinition->contentSize.x / (float)imageWidth * imageHeight;
	}
}

void Image::onAutoWidth(float& width) {
	if(!isImageLoaded)
		return;
		
	if(boxModel->height == core::Unit::Auto){
		width = imageWidth;
	}else{
		if(boxDefinition)
			width =  boxDefinition->contentSize.y / (float)imageHeight * imageWidth;
	}
}

void Image::contentSizeChanged(core::Point p) {
	//update the draw size
	drawSize = p;
}

void Image::unitTypeChanged(core::Unit::Type type) {
}

void Image::onBoxDefinition(BoxDefinition* boxDef) {
	boxDefinition = boxDef;
	boxDefinition->contentSize.changed.connect<Image, &Image::contentSizeChanged>(this);
}

void Image::onBoxModel(BoxModel* bm) {
	boxModel = bm;
	boxModel->width.typeChanged.connect<Image, &Image::unitTypeChanged>(this);
	boxModel->height.typeChanged.connect<Image, &Image::unitTypeChanged>(this);
	
	boxModel->onHeightAuto.connect<Image, &Image::onAutoHeight>(this);
	boxModel->onWidthAuto.connect<Image, &Image::onAutoWidth>(this);
}

void Image::onSerializer(Serializer* serializer) {
	serializer->deserialized.connect<Image, &Image::onDeserialize>(this);
}

void Image::onCss(Css* c) {
	css = c;
}

void Image::onDraw(Draw* draw) {
	draw->onDraw.connect<Image, &Image::drawIt>(this);
}

bool Image::loadImage(string path) {
	path = core::Globals::get().dataRoot + path;
	isImageLoaded = img.loadImage(path);
	imageWidth = img.width;
	imageHeight = img.height;
	return isImageLoaded;
}

void Image::onDeserialize(core::VariantList& variants) {
	if(variants.hasKey("src")) {
		loadImage(variants.get("src"));
	}
}


}
}
