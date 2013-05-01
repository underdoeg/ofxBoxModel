#include "testApp.h"
#include "core/Box.h"
#include "debug/DebugDraw.h"

using namespace ofx::boxModel::core;
using namespace ofx::boxModel::debug;

//--------------------------------------------------------------
void testApp::setup()
{
	Box box1;
	box1.margin = Unit::Pixel;
	Box box2;
	Box box3;
	DebugDraw::drawTree(&box1);
}

//--------------------------------------------------------------
void testApp::update()
{
	
}

//--------------------------------------------------------------
void testApp::draw()
{

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
