#pragma once

#include "ofMain.h"

#include "ofxBox.h"
#include "debug/DebugDrawer.h"
#include "tools/Instancer.h"
#include "tools/Xml.h"

class CustomBox: public ofxBox{
	string getType(){
		return "customBox";
	}
	
	void onMouseMove(float x, float y){
		cout << "MOVED" << endl;
	}
};

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
		
		
		boxModel::debug::DebugDrawer debugDrawer;
		ofxBox* rootBox;
 };
