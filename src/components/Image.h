	#ifndef IMAGE_H
#define IMAGE_H

#include "Component.h" // Base class: boxModel::core::Component
#include "BoxDefinition.h"
#include "Css.h"
#include "Draw.h"

namespace boxModel
{

namespace components
{

enum ImageFitMode{
	ImageFit,
	ImageScale,
	ImageAuto,
	ImageAutoWidth,
	ImageAutoHeight
};

class Image : public boxModel::core::Component
{
public:
	Image();
	~Image();
	
	void setup();
	std::string getName();
	bool loadImage(string path);
	
	core::Value<ImageFitMode> fitMode;
	
	int imageWidth;
	int imageHeight;
	int imageBpp;
	bool isImageLoaded;
	
private:
	void onBoxDefinition(BoxDefinition* boxDef);
	void onBoxModel(BoxModel* boxModel);
	void onCss(Css* css);
	void onSerializer(Serializer* serializer);
	void onDeserialize(core::VariantList& variants);
	void onDraw(Draw* draw);
	
	void recalculateBoxSize();
	
	void onAutoWidth(float& width);
	void onAutoHeight(float& height);
	
	void contentSizeChanged(core::Point);
	void unitTypeChanged(core::Unit::Type type);
	
	void drawIt();
	
	core::Point drawSize;
	
	BoxDefinition* boxDefinition;
	BoxModel* boxModel;
	Css* css;
	
	//TODO: decouple from OF
	ofImage img;
};

}
}

#endif // IMAGE_H
