#include "testApp.h"
#include "ofx/Renderer.h"

using namespace boxModel::tools;
using namespace boxModel::core;
using namespace boxModel::debug;

//--------------------------------------------------------------
void testApp::setup() {
	
	//set the renderer
	boxModel::components::Draw::renderer = new boxModel::ofx::Renderer();
	
	//add the customBox to the instancer system
	Instancer::addInstancer<CustomBox>();
	
	rootBox = Xml::load<boxModel::boxes::Box>(ofToDataPath("scene.xml"));
	rootBox->loadCss(ofToDataPath("style.css"));
	
	rootBox->width = ofGetWidth();
	rootBox->height = ofGetHeight();
	
	infoViewer.loadCss(ofToDataPath("infoViewer.css"));
	
	rootBox->addChild(&infoViewer);
	
	rootBox->flush();
	
	infoViewer.setComponentContainer(rootBox);
}

//--------------------------------------------------------------
void testApp::update() {

}

//--------------------------------------------------------------
void testApp::draw() {
	//debugDrawer.draw(rootBox);	
	rootBox->draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	rootBox->setMousePos(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
	rootBox->setMousePos(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	rootBox->setMouseButtonPressed(button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
	rootBox->setMouseButtonReleased(button);
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {
	rootBox->width = w;
	rootBox->height = h;
	rootBox->flush();
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}
