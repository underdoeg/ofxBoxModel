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
		//cout << "MOUSE " << x << " - " << y << endl;
	}
	
	void onMouseDrag(float x, float y, boxModel::components::Mouse::ButtonStates& buttons){
		cout << "MOUSE DRAG " << x << " - " << y << endl;
	}
	
	void onMouseEnter(float x, float y){
		cout << "MOUSE ENTER" << endl;
	}
	
	void onMouseExit(){
		cout << "MOUSE EXIT" << endl;
	}
	
	void onMouseClick(int button){
		cout << "mouse clicked " << button << endl;
	}
	
	void onMouseDoubleClick(int button){
		cout << "mouse double clicked " << button << endl;
	}
	
	void onMousePress(float x, float y, int button){
		cout << "button pressed " << button << endl;
	}
	
	void onMouseRelease(float x, float y, int button){
		cout << "button released " << button << endl;
	}
	
	void onMouseReleaseOutside(int button){
		cout << "button released outside " << button << endl;
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
