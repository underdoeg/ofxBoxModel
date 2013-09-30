#include "testApp.h"

using namespace boxModel::tools;
using namespace boxModel::core;
using namespace boxModel::debug;

//--------------------------------------------------------------
void testApp::setup() {
	
	//add the customBox to the instancer system
	Instancer::addInstancer<CustomBox>();
	
	rootBox = Xml::load<ofxBox>(ofToDataPath("scene.xml"));
	rootBox->loadCss(ofToDataPath("style.css"));
	
	rootBox->width = ofGetWidth();
	rootBox->height = ofGetHeight();
	
	rootBox->flush();
}

//--------------------------------------------------------------
void testApp::update() {

}

//--------------------------------------------------------------
void testApp::draw() {
	debugDrawer.draw(rootBox);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
	rootBox->width = w;
	rootBox->height = h;
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}
