#include "Serializer.h"

namespace boxModel
{

namespace components
{

Serializer::Serializer()
{
}

Serializer::~Serializer()
{
}

std::string Serializer::getName(){
	return "serializer";
}

void Serializer::setup()
{
}

void Serializer::deserialize(core::VariantList values)
{
	onDeserialize(values);
	deserialized(values);
	deserializeCompleted(values);
}

core::VariantList Serializer::serialize()
{
	core::VariantList values;
	serialized(values);
	return values;
}

void Serializer::getInfo(core::Component::Info& info){

}

}

}


