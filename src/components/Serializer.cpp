#include "Serializer.h"

namespace boxModel {

namespace components {

Serializer::Serializer() {
}

Serializer::~Serializer() {
}

std::string Serializer::getName() {
	return "serializer";
}

void Serializer::setup() {
}

void Serializer::deserialize(core::VariantList values) {
	deserializeValues = values;
	onDeserialize(deserializeValues);
	deserialized(deserializeValues);
	deserializeCompleted(deserializeValues);
}

core::VariantList& Serializer::getDeserializedValues() {
	return deserializeValues;
}

core::VariantList Serializer::serialize() {
	core::VariantList values;
	serialized(values);
	return values;
}

void Serializer::getInfo(core::Component::Info& info) {

}

}

}
