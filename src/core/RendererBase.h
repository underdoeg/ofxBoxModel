#ifndef RENDERERBASE_H
#define RENDERERBASE_H

#include "core/BaseTypes.h"

namespace boxModel {

namespace core {

class RendererBase;
	
class RendererResources{
public:
	class Image{
			public:
			Image(){
				width = 0;
				height = 0;
				bpp = 0;
				pixels = NULL;
			}
			~Image(){
				if(pixels != NULL)
					delete pixels;
			}
			unsigned int width;
			unsigned int height;
			unsigned int bpp;
			unsigned char* pixels;

		private:
			unsigned int id;
			friend class RendererResources;
	};

	static unsigned int addImage(unsigned char* pixels, unsigned int width, unsigned int height, unsigned int bpp);
	static Image& getImage(unsigned int id);
	static void removeImage(unsigned int id);
	static void addRenderer(RendererBase* renderer);

private:
	static unsigned int curImageId;
	static std::map<unsigned int, Image> images;
	static std::vector<RendererBase*> renderers;
};

class RendererBase {
public:

	typedef void* ImagePointer;

	RendererBase();
	~RendererBase();

	virtual void pushMatrix() = 0;
	virtual void popMatrix() = 0;
	virtual void translate(boxModel::core::Point pos) = 0;
	virtual void drawRect(boxModel::core::Point position, boxModel::core::Point size, boxModel::core::Color color) = 0;
	virtual void drawLine(boxModel::core::Point a, boxModel::core::Point b, boxModel::core::Color color, float width) = 0;

	virtual ImagePointer allocateImage(unsigned char* pixels, int width, int height, int bpp) = 0;
	virtual void drawImage(ImagePointer img) = 0;
	virtual void removeImage(ImagePointer img) = 0;
	
	void removeImage(unsigned int id);

	void drawImage(unsigned int imageId);

	boxModel::core::Color bgColor;
	boxModel::core::Color color;

private:
	bool hasImage(unsigned int id);

	std::map<int, ImagePointer> images;
};

}

}

#endif // RENDERERBASE_H
