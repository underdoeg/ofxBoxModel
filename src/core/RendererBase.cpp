#include "RendererBase.h"

namespace boxModel
{

namespace core
{

unsigned int RendererResources::curImageId = 0;
std::map<unsigned int, RendererResources::Image> RendererResources::images;

unsigned int RendererResources::addImage(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int bpp)
{
	Image& img = images[curImageId];
	img.height = height;
	img.width = width;
	img.bpp = bpp;
	img.id = curImageId;
	img.pixels = pixels;
	curImageId++;

	return img.id;
}

RendererResources::Image& RendererResources::getImage(unsigned int id)
{
	return images[id];
}

void RendererResources::removeImage(unsigned int id)
{
	//delete images[id].pixels;
	images.erase(id);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RendererBase::RendererBase()
{
}

RendererBase::~RendererBase()
{
}

void RendererBase::drawImage(unsigned int id)
{
	if(!hasImage(id)){
		RendererResources::Image& img = RendererResources::getImage(id);
		images[id] = allocateImage(img.pixels, img.width, img.height, img.bpp);
		//((ofImage*)images[id])->saveImage("export/img-"+ofToString(id)+".png");
	}
	drawImage(images[id]);
}

bool boxModel::core::RendererBase::hasImage(unsigned int id)
{
	return images.find(id) != images.end();
}

}}


