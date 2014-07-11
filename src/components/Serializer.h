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
	
	Nano::Signal<void(core::VariantList&)> serialized;
	Nano::Signal<void(core::VariantList&)> deserialized;
	Nano::Signal<void(core::VariantList&)> deserializeCompleted;
	
	core::VariantList& getDeserializedValues();
	core::VariantList serialize();
	void deserialize(core::VariantList values);
	void getInfo(core::Component::Info& info);
	
	virtual void onDeserialize(boxModel::core::VariantList& variants){};

public:
	core::VariantList deserializeValues;
	void setup();
};

}

}

#endif // SERIALIZE_H
