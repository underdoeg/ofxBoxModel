#include "RendererBase.h"

namespace boxModel {

namespace core {

unsigned int RendererResources::curImageId = 0;
std::map<unsigned int, RendererResources::Image> RendererResources::images;
std::vector<RendererBase*> RendererResources::renderers;

unsigned int RendererResources::addImage(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int bpp) {
	Image& img = images[curImageId];
	img.height = height;
	img.width = width;
	img.bpp = bpp;
	img.id = curImageId;
	img.pixels = new unsigned char[width * height * bpp];
	memcpy(img.pixels, pixels, width*height*bpp);
	img.pixels = pixels;
	curImageId++;

	return img.id;
}

RendererResources::Image& RendererResources::getImage(unsigned int id) {
	return images[id];
}

void RendererResources::removeImage(unsigned int id) {
	//cout << "REMOVE IMAGE" << endl;
	//delete[] images[id].pixels;
	images.erase(id);
	for(RendererBase* renderer: renderers){
		renderer->removeImage(id);
	}
}

void RendererResources::addRenderer(RendererBase* renderer) {
	renderers.push_back(renderer);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RendererBase::RendererBase() {
	RendererResources::addRenderer(this);
}

RendererBase::~RendererBase() {
}

void RendererBase::drawImage(unsigned int id) {
	if(!hasImage(id)) {
		RendererResources::Image& img = RendererResources::getImage(id);
		images[id] = allocateImage(img.pixels, img.width, img.height, img.bpp);
		//((ofImage*)images[id])->saveImage("export/img-"+ofToString(id)+".png");
	}
	drawImage(images[id]);
}

void RendererBase::removeImage(unsigned int id) {
	if(hasImage(id)){
		removeImage(images[id]);
		images.erase(id);
	}
}

bool boxModel::core::RendererBase::hasImage(unsigned int id) {
	return images.find(id) != images.end();
}

}
}
