#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup() {
	
	/*
	rootBox.width = ofGetWidth();
	rootBox.height = ofGetHeight();
	//rootBox.setBgColor(20);
	
	rootBox.setId("root");
	*/
	
	/*
	for(int i=0;i<4;i++){
		ofxBox* b = new ofxBox();
		b->addClass("quarter");
		rootBox.addChild(b);
	}
	*/
	
	/*
	for(unsigned int i = 0; i<20; i++) {
		ofxBox* b = new CustomBox();
		b->width = ofRandom(100, 150);
		b->height = 100;
		b->floating = FloatLeft;
		b->addClass("outerBox");

		int amount = ofRandom(2, 20);

		for(int j=0; j<amount; j++) {
			ofxBox* b2 = new CustomBox();
			b2->addClass("innerBox");
			b->addChild(b2);
			b2->floating = FloatLeft;
		}
		rootBox.addChild(b);
	}
	*/
	//rootBox.loadCss("style.css");
	
	//rootBox.loadXmlInto(ofToDataPath("output.xml"));
	
	//rootBox.saveAsXml(ofToDataPath("output.xml"));

	rootBox = ofxBox::loadXml(ofToDataPath("output.xml"));
}

//--------------------------------------------------------------
void testApp::update() {

}

//--------------------------------------------------------------
void testApp::draw() {
	debugDrawer.drawTree(rootBox);
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
