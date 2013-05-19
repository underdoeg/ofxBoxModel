#include "ofxBox.h"

ofxBox::ofxBox()
{
}

ofxBox::~ofxBox()
{
}

std::string ofxBox::getType(){
	return "ofxBox";
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
