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
	void linkTo(Linker* linker);
	Nano::signal<void(Linker* linker)> linkedTo;
private:
	void onLayouter(Layouter* layouter);
	void onSerializer(Serializer* s);
	void onSerialize(core::VariantList& variants);
	void onDeserialize(core::VariantList& variants);
	
	void onOverflow(std::vector<core::ComponentContainer*>);
	
	Linker* linker;
	Layouter* layouter;
	string linkToAddress;
};

}

}

#endif // LINKER_H
