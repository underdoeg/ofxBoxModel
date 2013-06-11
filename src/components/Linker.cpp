#include "Linker.h"

namespace boxModel
{

namespace components
{

Linker::Linker():linker(NULL)
{
	
}

Linker::~Linker()
{
	
}

void Linker::setup()
{
	LISTEN_FOR_COMPONENT(Layouter, Linker, onLayouter)
	LISTEN_FOR_COMPONENT(Serializer, Linker, onSerializer)
}

void Linker::onLayouter(Layouter* l)
{
	layouter = l;
}

void Linker::onSerializer(Serializer* ser){
	ser->deserialized.connect<Linker, &Linker::onDeserialize>(this);
	ser->serialized.connect<Linker, &Linker::onSerialize>(this);
}

void Linker::onSerialize(core::VariantList& variants){
	
}

void Linker::onDeserialize(core::VariantList& variants){
	if(variants.hasKey("linkTo")){
		if(components->hasComponent<Stack>()){
			Stack* stack = components->getComponent<Stack>();
			
		}
	}
}

void Linker::linkTo(Linker* l)
{
	linker = l;
	linkedTo(linker);
}

}

}


