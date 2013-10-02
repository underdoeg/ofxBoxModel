#include "Linker.h"

using namespace std;
using namespace boxModel::core;

using namespace boxModel::components;

Linker::Linker():linkerTo(NULL) {

}

Linker::~Linker() {

}

std::string Linker::getName(){
	return "linker";
}

void Linker::setup() {
	LISTEN_FOR_COMPONENT(Layouter, Linker, onLayouter)
	LISTEN_FOR_COMPONENT(Serializer, Linker, onSerializer)
	LISTEN_FOR_COMPONENT(Stack, Linker, onStack)
}

void Linker::copyFrom(Linker* linker)
{
	linkToAddress = linker->linkToAddress;
}

void Linker::onLayouter(Layouter* l) {
	layouter = l;
	layouter->overflowed.connect<Linker, &Linker::onOverflow>(this);
}

void Linker::onStack(Stack* s) {
	stack = s;
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
	if(linkerTo == NULL && linkToAddress.size()>0) {
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

	if(linkerTo == NULL)
		return;

	if(linkerTo->components->hasComponent<Stack>()) {
		//now add the overflowed components to the next linker
		Stack* linkerStack = linkerTo->components->getComponent<Stack>();
		linkerStack->addChildren(compList);
		
		/*
		layouter->layout();
		if(linkerStack->components->hasComponent<Layouter>()){
			linkerStack->components->getComponent<Layouter>()->layout();
		}
		*/
	}
	overflowed.insert(overflowed.end(), compList.begin(), compList.end());
	
	//add listener to remove a container if it gets deleted
	for(ComponentContainer* c: overflowed){
		c->deleted.connect<Linker, &Linker::onContainerDeleted>(this);
	}
	
	linkedTo(linkerTo);
}

void Linker::unlink()
{
	cout << "UNLINK " << overflowed.size() << endl;
	if(stack != NULL){
		
		for(ComponentContainer* c: overflowed){
			c->deleted.disconnect<Linker, &Linker::onContainerDeleted>(this);
		}
		stack->addChildren(overflowed);
		
		overflowed.clear();
	}
}

void Linker::linkTo(Linker* l) {
	if(linkerTo == l)
		return;
	if(linkerTo != NULL)
		linkerTo->removeLinkerFrom(this);
	linkerTo = l;
	linkerTo->addLinkerFrom(this);
	if(linkerTo->components->hasComponent<Layouter>()){
		linkerTo->components->getComponent<Layouter>()->preLayouted.connect<Linker, &Linker::onPreLayout>(this);
	}
}

Linker* Linker::getLinkTo()
{
	updateLinkTo();
	return linkerTo;
}

void Linker::onContainerDeleted(core::ComponentContainer* container)
{
	overflowed.erase(std::remove(overflowed.begin(), overflowed.end(), container), overflowed.end());
}

void Linker::onLayout()
{
	/*
	if(layouter != NULL)
		layouter->layout();
	*/
}

void Linker::onPreLayout()
{
	//unlink();
}

void Linker::addLinkerFrom(Linker* linker)
{
	if(linker->components->hasComponent<Layouter>()){
		linker->components->getComponent<Layouter>()->layouted.connect<Linker, &Linker::onLayout>(this);
	}
}

void Linker::removeLinkerFrom(Linker* linker)
{
	if(linker->components->hasComponent<Layouter>()){
		linker->components->getComponent<Layouter>()->layouted.disconnect<Linker, &Linker::onLayout>(this);
	}
}

void Linker::getInfo(core::Component::Info& info){

}