#include "Linker.h"

using namespace std;
using namespace boxModel::core;

using namespace boxModel::components;

Linker::Linker():linker(NULL) {

}

Linker::~Linker() {

}

void Linker::setup() {
	LISTEN_FOR_COMPONENT(Layouter, Linker, onLayouter)
	LISTEN_FOR_COMPONENT(Serializer, Linker, onSerializer)
}

void Linker::copyFrom(Linker* linker)
{
	linkToAddress = linker->linkToAddress;
}

void Linker::onLayouter(Layouter* l) {
	layouter = l;
	layouter->overflowed.connect<Linker, &Linker::onOverflow>(this);
}

void Linker::onSerializer(Serializer* ser) {
	ser->deserialized.connect<Linker, &Linker::onDeserialize>(this);
	ser->serialized.connect<Linker, &Linker::onSerialize>(this);
}

void Linker::onSerialize(core::VariantList& variants) {

}

void Linker::onDeserialize(core::VariantList& variants) {
	if(variants.hasKey("linkTo")) {
		//have to store the address in a string because depending on the parsing the link target does not yet have the id
		linkToAddress = variants.get("linkTo");
	}
}

void Linker::updateLinkTo()
{
	if(linker == NULL && linkToAddress.size()>0) {
		if(components->hasComponent<Stack>()) {
			Stack* stack = components->getComponent<Stack>();
			stack = stack->getUltimateParent();
			if(stack->components->hasComponent<Addressable>()) {
				std::vector<Addressable*> elements = stack->components->getComponent<Addressable>()->findByAddress(linkToAddress);
				if(elements.size()>0)
					if(elements[0]->components->hasComponent<Linker>())
						linkTo(elements[0]->components->getComponent<Linker>());
			}
		}
	}
}

void Linker::onOverflow(std::vector<ComponentContainer*> compList) {
	updateLinkTo();

	if(linker == NULL)
		return;

	if(linker->components->hasComponent<Stack>()) {
		//now add the overflowed components to the next linker
		Stack* linkerStack = linker->components->getComponent<Stack>();
		linkerStack->addChildren(compList);
		
		layouter->layout();
		if(linkerStack->components->hasComponent<Layouter>()){
			linkerStack->components->getComponent<Layouter>()->layout();
		}
		
	}
	
	linkedTo(linker);
}

void Linker::linkTo(Linker* l) {
	linker = l;
}

Linker* Linker::getLinkTo()
{
	updateLinkTo();
	return linker;
}
