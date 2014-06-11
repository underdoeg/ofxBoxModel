
#include "Instancer.h"
#include "boxes/Box.h"
#include "boxes/Texts.h"
#include "gui/Button.h"

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
	
	addInstancer<boxes::Box>("box");
	addInstancer<boxes::TextBox>("text");
	addInstancer<boxes::H1>("h1");
	addInstancer<boxes::H2>("h2");
	addInstancer<boxes::H3>("h3");
	addInstancer<gui::Button>("button");
	
	isSetup = true;
}

}

}

