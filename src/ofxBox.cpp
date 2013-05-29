#include "ofxBox.h"

ofxBox::ofxBox()
{
	addInstancer<ofxBox>(this);
}

ofxBox::~ofxBox()
{
}

std::string ofxBox::getType(){
	return "box";
}

void ofxBox::popMatrix()
{
	ofPopMatrix();
}

void ofxBox::pushMatrix()
{
	ofPushMatrix();
}

void ofxBox::translateMatrix(float x, float y)
{
	ofTranslate(x, y);
}
