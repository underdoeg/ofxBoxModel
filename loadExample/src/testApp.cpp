#include "testApp.h"
#include "ofx/Renderer.h"

using namespace boxModel::tools;
using namespace boxModel::core;
using namespace boxModel::debug;

//--------------------------------------------------------------
void testApp::setup() {

	ofSetFrameRate(60);

	ofEnableAlphaBlending();

	//set the renderer
	boxModel::components::Draw::setRenderer(new boxModel::ofx::Renderer());
	Globals::get().dataRoot = ofToDataPath("", true) + "";

	//add the customBox to the instancer system
	Instancer::addInstancer<CustomBox>();

	//load the structure
	rootBox = Xml::load<boxModel::boxes::Box>("scene.xml");
	rootBox->loadCss("style.css");

	rootBox->width = ofGetWidth();
	rootBox->height = ofGetHeight();

	rootBox->flush();

	//infoViewer.loadCss(ofToDataPath("infoViewer.css"));
	//rootBox->addChild(&infoViewer);
	//infoViewer.setComponentContainer(rootBox);

	//assign the debugger
	debugger.setComponentContainer(rootBox);
	debugger.loadCss("debugger.css");
	//debugger.hide();

	//boxModel::boxes::TextBox* tb = rootBox->findByAddress<boxModel::boxes::TextBox>("p")[0];
}

//--------------------------------------------------------------
void testApp::update() {

}

//--------------------------------------------------------------
void testApp::draw() {
	//debugDrawer.draw(rootBox);
	//debugDrawer.draw(&debugger);
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
