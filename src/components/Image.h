	#ifndef IMAGE_H
#define IMAGE_H

#include "Component.h" // Base class: boxModel::core::Component
#include "BoxDefinition.h"
#include "Css.h"

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
	
	core::Value<ImageFitMode> fitMode;
	
private:
	void onBoxDefinition(BoxDefinition* boxDef);
	void onCss(Css* css);
	
	BoxDefinition* boxDefinition;
	Css* css;
};

}
}

#endif // IMAGE_H
