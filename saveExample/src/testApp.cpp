#include "testApp.h"

void testApp::setup(){
	
	root.setId("root");
	
	root.width = ofGetWidth();
	root.height = ofGetHeight();
	for(unsigned int i = 0; i<220; i++) {

		ofxBox* b = new CustomBox();
		
		b->width = ofRandom(100, 150);
		b->height = 100;
		b->height = Unit::Auto;
		b->floating = FloatLeft;
		b->padding = 5;
			
		b->addClass("outerBox");
		
		int amount = ofRandom(2, 200);

		for(int j=0; j<amount; j++) {
			ofxBox* b2 = new CustomBox();
			b2->addClass("innerBox");
			b2->width = 4;
			b2->height = 4;
			b2->floating = FloatLeft;
			b->addChild(b2);
		}
		
		root.addChild(b);		
	}
	
	//rootBox.loadCss("style.css");
	
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
