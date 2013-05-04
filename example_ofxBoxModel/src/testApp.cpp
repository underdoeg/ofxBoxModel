#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup()
{
	box1.width = 200;
	box1.height = 200;
	box1.margin = Unit::Pixel;
	
	Layouter l;
	l.layout(&box1);
}

//--------------------------------------------------------------
void testApp::update()
{
	
}

//--------------------------------------------------------------
void testApp::draw()
{
	debugDrawer.drawBox(&box1);
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
