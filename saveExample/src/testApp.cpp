#include "testApp.h"

void testApp::setup(){
	
	Instancer::addInstancer<ofxBox>();
	Instancer::addInstancer<CustomBox>();
	/*
	root.setId("root");
	
	root.width = ofGetWidth();
	root.height = ofGetHeight();
	for(unsigned int i = 0; i<10; i++) {

		CustomBox* b = new CustomBox();
				
		b->width = 112;
		b->height = 100;
		b->height = Unit::Auto;
		b->floating = FloatLeft;
		b->padding = 5;
		b->margin =  5;
			
		b->addClass("outerBox");
		
		b->setBgColor(20);
		
		root.addChild(b);		
		
		int amount = ofRandom(2, 90);

		for(int j=0; j<amount; j++) {
			ofxBox* b2 = new CustomBox();
			b2->addClass("innerBox");
			b->addChild(b2);
		}
		
	}
	
	root.loadCss(ofToDataPath("style.css", true));
	
	//child.addClass("test");
	//cout << root.findByAddress(".innerBox").size() << endl;
	*/
	xmlRoot = Xml::load<ofxBox>(ofToDataPath("tree.xml"));
	
	xmlRoot->loadCss(ofToDataPath("style.css"));
	
}

//--------------------------------------------------------------
void testApp::update() {
	//root.width = ofGetWidth();
	//root.height = ofGetHeight();
}

//--------------------------------------------------------------
void testApp::draw() {
	
	debugDrawer.draw(xmlRoot);
	
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
