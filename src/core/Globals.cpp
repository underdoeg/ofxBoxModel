#include "Globals.h"

namespace boxModel
{

namespace core
{

Globals Globals::instance;
	
Globals::Globals()
{
	
}

Globals::~Globals()
{
}

Globals& Globals::get(){
	return instance;
}

}

}

