#pragma once

#include "ofMain.h"

#include "core/Box.h"
#include "layout/Layouter.h"
#include "debug/DebugDrawer.h"

using namespace ofx::boxModel::core;
using namespace ofx::boxModel::debug;
using namespace ofx::boxModel::layout;

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
		
		DebugDrawer<Box> debugDrawer;
		Box box1, box2, box3;
};
