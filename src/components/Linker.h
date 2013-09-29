#ifndef LINKER_H
#define LINKER_H

#include "core/Component.h"
#include "Layouter.h"

namespace boxModel {

namespace components {

class Linker: public core::Component {
public:
	Linker();
	~Linker();
	void setup();
	void linkTo(Linker* linkerTo);
	void unlink();
	Linker* getLinkTo();
	Nano::signal<void(Linker* linkerTo)> linkedTo;
	Nano::signal<void(Linker* linkerTo)> movedTo;
	
	void copyFrom(Linker* linkerTo);
	
private:
	void addLinkerFrom(Linker* linker);
	void removeLinkerFrom(Linker* linker);
	void updateLinkTo();
	void onContainerDeleted(core::ComponentContainer* container);

	void onLayouter(Layouter* layouter);
	void onSerializer(Serializer* s);
	void onStack(Stack* stack);
	
	void onLayout();
	void onPreLayout();

	void onSerialize(core::VariantList& variants);
	void onDeserialize(core::VariantList& variants);
	
	void onOverflow(std::vector<core::ComponentContainer*> components);
	
	Linker* linkerTo;
	//Linker* linkerFrom;
	Layouter* layouter;
	Stack* stack;
	string linkToAddress;
	std::vector<core::ComponentContainer*> overflowed;
};

}

}

#endif // LINKER_H
