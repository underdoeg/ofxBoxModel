#include "testApp.h"

using namespace ofx::BoxModel;

//--------------------------------------------------------------
void testApp::setup(){
	root.definition.width = ofGetWidth();
	root.definition.height = ofGetHeight();
	
	for(int i=0;i<4;i++){
		Box* b = root.createChild();
		b->definition.width = 50;
		b->definition.width = Unit::Percent;
		b->definition.height = 50;
		b->definition.height = Unit::Percent;
		b->definition.marginLeft = 25;
		b->definition.marginLeft = Unit::Percent;
	}
	
	/*
	for(int i=0;i<60;i++){
		Box* b = root.createChild();
		b->definition.width = ofRandom(100, 200);
		b->definition.height = ofRandom(100, 200);
		b->definition.setMargin(ofRandom(0, 10));
		b->definition.setPadding(ofRandom(0, 30));
		for(int j=0;j<ofRandom(0, 50); j++){
			Box* bb = b->createChild();
			bb->definition.width = ofRandom(10, 20);
			bb->definition.height = ofRandom(10, 20);
		}
	}
	*/
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255);
	root.debugDraw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	root.definition.width = w;
	root.definition.height = h;
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}