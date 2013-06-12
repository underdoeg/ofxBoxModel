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
	cout << "HOHOO" << endl;
	if(variants.hasKey("linkTo")){
		if(components->hasComponent<Stack>()){
			Stack* stack = components->getComponent<Stack>();
			stack = stack->getUltimateParent();
			if(stack->components->hasComponent<Addressable>()){
				std::vector<Addressable*> elements = stack->components->getComponent<Addressable>()->findByAddress(variants.get("linkTo"));
				if(elements.size()>0)
					if(elements[0]->components->hasComponent<Linker>())
						linkTo(elements[0]->components->getComponent<Linker>());
			}
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


