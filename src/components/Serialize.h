#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "Component.h" // Base class: boxModel::core::Component
#include "core/BaseTypes.h"
#include "core/Utils.h"
#include <unordered_map>

namespace boxModel {

namespace components {

class Serialize : public boxModel::core::Component {
public:
	Serialize();
	~Serialize();
	
	Nano::signal<void(core::VariantList&)> serialized;
	Nano::signal<void(core::VariantList&)> deserialized;
	
	core::VariantList serialize();
	void deserialize(core::VariantList values);
	
public:
	void setup();
};

}

}

#endif // SERIALIZE_H
