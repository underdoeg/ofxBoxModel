#include "testApp.h"

void testApp::setup(){
	
	root.setId("root");
	
	root.width = ofGetWidth();
	root.height = ofGetHeight();
	for(unsigned int i = 0; i<10; i++) {

		ofxBox* b = new CustomBox();
		
		b->width = ofRandom(100, 150);
		b->height = 100;
		b->height = Unit::Auto;
		b->floating = FloatLeft;
		b->padding = 5;
		b->margin =  5;
			
		b->addClass("outerBox");
		
		b->setBgColor(255, 0,0 );
		
		int amount = ofRandom(2, 50);
		
		for(int j=0; j<amount; j++) {
			ofxBox* b2 = new CustomBox();
			b2->addClass("innerBox");
			b->addChild(b2);
		}
		
		root.addChild(b);		
	}
	
	root.loadCss(ofToDataPath("style.css", true));
	
	//child.addClass("test");
	//cout << root.findByAddress(".innerBox").size() << endl;
}

//--------------------------------------------------------------
void testApp::update() {
	root.width = ofGetWidth();
	root.height = ofGetHeight();
}

//--------------------------------------------------------------
void testApp::draw() {
	
	
	debugDrawer.draw(&root);
	
	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 30, 30);
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
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}
