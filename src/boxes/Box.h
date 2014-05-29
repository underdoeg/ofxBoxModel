#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "core/Component.h"
#include "components/Addressable.h"
#include "components/BoxModel.h"
#include "components/Stack.h"
#include "components/BoxDefinition.h"
#include "components/Layouter.h"
#include "components/Style.h"
#include "components/Css.h"
#include "components/Serializer.h"
#include "components/Linker.h"
#include "components/Splitter.h"
#include "components/Mouse.h"
#include "components/Draw.h"

namespace boxModel {
namespace boxes {

class Box:
	public boxModel::core::ComponentContainer, public boxModel::components::Addressable, public boxModel::components::Stack,
	public boxModel::components::BoxDefinition, public boxModel::components::BoxModel, public boxModel::components::Style,
	public boxModel::components::Css, public boxModel::components::Serializer, public boxModel::components::Linker,
	public boxModel::components::Splitter, public boxModel::components::Mouse, public boxModel::components::Draw {
public:
	Box() {
		addComponent<boxModel::components::Stack>(this);
		addComponent<boxModel::components::Addressable>(this);
		addComponent<boxModel::components::BoxDefinition>(this);
		addComponent<boxModel::components::BoxModel>(this);
		addComponent<boxModel::components::Layouter>(&layouter);
		addComponent<boxModel::components::Style>(this);
		addComponent<boxModel::components::Css>(this);
		addComponent<boxModel::components::Serializer>(this);
		addComponent<boxModel::components::Linker>(this);
		addComponent<boxModel::components::Splitter>(this);
		addComponent<boxModel::components::Mouse>(this);
		addComponent<boxModel::components::Draw>(this);

		deserialized.connect<Box, &Box::onDeserialize>(this);
	}

	virtual ~Box() {};

	virtual string getType() {
		return "box";
	}

	virtual void onDeserialize(boxModel::core::VariantList& variants) {};
	virtual void onMouseDrag(float mouseX, float mouseY, ButtonStates& buttons){};
	virtual void test(){};

	boxModel::components::Layouter layouter;
};


}
}
#endif // BOXMODEL_H
