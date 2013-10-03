
#include "Instancer.h"
#include "boxes/Box.h"
#include "boxes/Texts.h"

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
	
	addInstancer<boxes::Box>();
	addInstancer<boxes::TextBox>();
	addInstancer<boxes::H1>();
	addInstancer<boxes::H2>();
	addInstancer<boxes::H3>();
	
	isSetup = true;
}

}

}

