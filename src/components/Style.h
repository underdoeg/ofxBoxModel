#ifndef STYLE_H
#define STYLE_H

#include "core/Component.h" // Base class: boxModel::core::Component
#include "core/BaseTypes.h"
#include "core/Unit.h"

namespace boxModel
{

namespace components
{

class Style : public core::Component
{
public:
	Style()
	{
		color.set(0);
		bgColor.set(255);
		borderColor.set(0);
		bBgColor = true;
	}
	~Style()
	{
	}

	virtual void setup()
	{
	}
	
	void setColor(core::Color c) {
		color.set(c);
	}

	void setColor(int gray, int alpha=255) {
		color.set(gray, alpha);
	}

	void setColor(int r, int g, int b, int alpha=255) {
		color.set(r, g, b, alpha);
	}

	core::Color getColor() {
		return color;
	}

	void setBgColorNone() {
		bBgColor = false;
	}

	void setBgColor(core::Color c) {
		bgColor.set(c);
		bBgColor = true;
	}

	void setBgColor(int gray, int alpha=255) {
		bgColor.set(gray, alpha);
		bBgColor = true;
	}

	void setBgColor(int r, int g, int b, int alpha=255) {
		bgColor.set(r, g, b, alpha);
		bBgColor = true;
	}

	bool hasBgColor() {
		return bBgColor;
	}

	core::Color getBgColor() {
		return bgColor;
	}

	void setBorderColor(core::Color c) {
		borderColor.set(c);
	}

	void setBorderColor(int gray, int alpha=255) {
		borderColor.set(gray, alpha);
	}

	void setBorderColor(int r, int g, int b, int alpha=255) {
		borderColor.set(r, g, b, alpha);
	}

	core::Color getBorderColor() {
		return borderColor;
	}
private:
	core::Color color;
	core::Color bgColor;
	core::Color borderColor;
	bool bBgColor;
};

}

}

#endif // STYLE_H
