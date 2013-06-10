#pragma once

#include "ofMain.h"
#include "ofxBox.h"
#include "debug/DebugDrawer.h"
#include "tools/Instancer.h"
#include "tools/Xml.h"

using namespace boxModel::core;
using namespace boxModel::tools;
using namespace boxModel::debug;
using namespace boxModel::components;

class CustomBox: public ofxBox{
public:
	string getType(){
		return "customBox";
	}
};
/*
class TextBox: public ofxBox, public Text{
public:
	TextBox(){
		addComponent<Text>(this);
	}
	
	string getType(){
		return "text";
	}
};
*/

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxBox root;
		
		ofxBox* xmlRoot;
		
		DebugDrawer debugDrawer;
 };
