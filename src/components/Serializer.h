#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "Component.h" // Base class: boxModel::core::Component
#include "core/BaseTypes.h"
#include "core/Utils.h"
#include <unordered_map>


namespace boxModel {

namespace components {

class Serializer : public boxModel::core::Component {
public:
	Serializer();
	~Serializer();
	
	std::string getName();
	
	Nano::signal<void(core::VariantList&)> serialized;
	Nano::signal<void(core::VariantList&)> deserialized;
	Nano::signal<void(core::VariantList&)> deserializeCompleted;
	
	core::VariantList serialize();
	void deserialize(core::VariantList values);
	void getInfo(core::Component::Info& info);

public:
	void setup();
};

}

}

#endif // SERIALIZE_H
