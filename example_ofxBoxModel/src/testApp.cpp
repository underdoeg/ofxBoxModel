#include "testApp.h"


using namespace ofx::boxModel::core;

//--------------------------------------------------------------
void testApp::setup()
{
	rootBox.width = ofGetWidth();
	rootBox.height = ofGetHeight();

	for(unsigned int i = 0;i<10;i++){
		Box* b = new Box();
		b->width = ofRandom(20, 100);
		b->height = 100;
		b->floating = FloatLeft;
		rootBox.addChild(b);
	}
	
	l.layout(&rootBox);
}

//--------------------------------------------------------------
void testApp::update()
{
	
}

//--------------------------------------------------------------
void testApp::draw()
{
	debugDrawer.drawTree(&rootBox);
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
	//root.props.width = w;
	//root.props.height = h;
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
