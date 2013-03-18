#include "testApp.h"

using namespace ofx::BoxModel;

//--------------------------------------------------------------
void testApp::setup()
{
	root.props.width = ofGetWidth();
	root.props.height = ofGetHeight();
	
	/*
	for(int i=0;i<4;i++){
		Box* b = root.createChild();
		b->props.width = 50;
		b->props.width = Unit::Percent;
		b->props.height = 50;
		b->props.height = Unit::Percent;
		b->props.floating = Properties::Left;
		b->props.setPadding(20);
	}
	*/
	
	for(int i=0;i<60;i++){
		Box* b = root.createChild();
		if(ofRandom(0,1) < .05)
			b->props.clear = true;
		b->props.floating = Properties::Left;
		b->props.width = ofRandom(100, 200);
		b->props.height = ofRandom(100, 200);
		b->props.setMargin(ofRandom(0, 10));
		b->props.setPadding(ofRandom(0, 30));
		for(int j=0;j<ofRandom(0, 50); j++){
			Box* bb = b->createChild();
			bb->props.floating = Properties::Left;
			bb->props.width = ofRandom(10, 20);
			bb->props.height = ofRandom(10, 20);
		}
	}

	Box* b = root.createChild();
	b->props.width = 500;
	b->props.height = 500;
	b->props.marginLeft = -b->props.width*.5;
	b->props.marginTop = -b->props.height*.5;
	b->props.left = 50;
	b->props.left = Unit::Percent;
	b->props.top = 50;
	b->props.top = Unit::Percent;
	b->props.position = Properties::Absolute;
	
}

//--------------------------------------------------------------
void testApp::update()
{
	
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground(255);
	root.debugDraw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
	root.props.width = w;
	root.props.height = h;
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
