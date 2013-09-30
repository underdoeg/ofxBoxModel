
#include "Instancer.h"
#include "ofxBox.h"

namespace boxModel {

namespace tools {

std::unordered_map<std::string, InstancerHelperBase*> Instancer::instancers;
bool Instancer::isSetup = false;

Instancer::Instancer() {
}

Instancer::~Instancer() {
}

void Instancer::setup()
{
	if(isSetup)
		return;
	
	addInstancer<ofxBox>();
	addInstancer<ofxBox>("box");
	
	isSetup = true;
}

}

}

