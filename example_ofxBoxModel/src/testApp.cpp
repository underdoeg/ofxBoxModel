#include "testApp.h"



using namespace ofx::boxModel::core;

//--------------------------------------------------------------
void testApp::setup() {
	rootBox.width = ofGetWidth();
	rootBox.height = ofGetHeight();
	//rootBox.setBgColor(20);
	
	rootBox.setId("root");
	
	/*
	for(int i=0;i<4;i++){
		Box* b = new Box();
		b->addClass("quarter");
		rootBox.addChild(b);
	}
	*/
	
	for(unsigned int i = 0; i<20; i++) {
		Box* b = new Box();
		b->width = ofRandom(100, 150);
		b->height = 100;
		b->floating = FloatLeft;
		b->addClass("outerBox");

		//b->setBgColor((int)ofRandom(255), (int)ofRandom(255), (int)ofRandom(255));
		//b->setColor((int)ofRandom(255), (int)ofRandom(255), (int)ofRandom(255));

		int amount = ofRandom(2, 20);

		for(int j=0; j<amount; j++) {
			Box* b2 = new Box();
			b2->addClass("innerBox");
			b->addChild(b2);
			b2->floating = FloatLeft;
		}
		rootBox.addChild(b);
	}
	
	
	//rootBox.setColorChildren(Color(200));

	rootBox.loadCss("style.css");

	//std::vector<Box*> boxes = rootBox.findByAddress("#idTest .classTest box");
	//cout << boxes.size() << endl;
}

//--------------------------------------------------------------
void testApp::update() {

}

//--------------------------------------------------------------
void testApp::draw() {
	debugDrawer.drawTree(&rootBox);
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
	rootBox.width = w;
	rootBox.height = h;
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}
