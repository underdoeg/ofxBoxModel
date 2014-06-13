#include "Css.h"
#include <fstream>
#include <streambuf>
#include "Globals.h"

using namespace boxModel::components;
using namespace boxModel::core;
using namespace std;

std::string Css::getName() {
	return "css";
}

void Css::setup() {
	isCssDirty = true;
	addressable = NULL;
	stack = NULL;
	LISTEN_FOR_COMPONENT(Serializer, Css, onSerializer)
	LISTEN_FOR_COMPONENT(Stack, Css, onStack)
	LISTEN_FOR_COMPONENT(Addressable, Css, onAddressable)
}

void Css::copyFrom(Css* css) {
	properties = css->properties;
	propertiesOrder = css->propertiesOrder;
}

void Css::loadCss(std::string path) {
	setCss(stringLoadFromFile(Globals::get().dataRoot+path));
}

void Css::setCss(std::string cssDefinition) {
	//first remove lin breaks & split for blocks
	cssDefinition = stringRemoveLineBreaks(cssDefinition);

	//remove comments
	std::vector<std::string> commentBlocks = stringSplit(cssDefinition, "*/");
	cssDefinition = "";
	for(std::string block: commentBlocks) {
		std::string key("/*");

		block = stringTrim(block);

		bool doIt = true;
		if(block.size()>1)
			if(block[0] == '/' && block[1] == '*')
				doIt = false;

		if(doIt) {
			std::vector<std::string> commentBlocks2 = stringSplit(block, key);
			string toAdd = stringTrim(commentBlocks2[0]);
			cssDefinition += toAdd;

		}
	}

//split by blocks
	std::vector<std::string> blocks = stringSplit(cssDefinition, '}');

//loop all blocks
	for(std::vector<std::string>::iterator itBlock = blocks.begin(); itBlock<blocks.end(); itBlock++) {
		std::string block = stringTrim(*itBlock);
		if(block.size() != 0) {
			std::vector<std::string> addressAndProperties = stringSplit(*itBlock, '{');
			if(addressAndProperties.size() == 2) {

				//now we have the address
				string address = stringTrim(addressAndProperties[0]);
				string propertiesString = addressAndProperties[1];

				std::vector<CssProperty> props = parseCssBlock(propertiesString);
				properties[address].insert(properties[address].end(), props.begin(), props.end());
				propertiesOrder.push_back(address);
			} else {
				debug::warning("CSS ERROR near "+addressAndProperties[0]);
			}
		}
	}

//printProperties();

	//

	setCssDirty(true, true);

	applyCss();

	cssChanged(this);
}

std::vector<CssProperty> Css::parseCssBlock(std::string propertiesString) {
	std::vector<CssProperty> ret;

	std::vector<std::string> propertyList = stringSplit(propertiesString, ';');

	//now parse all properties
	for(std::vector<std::string>::iterator itProp = propertyList.begin(); itProp<propertyList.end(); itProp++) {
		std::vector<std::string> keyAndValue= stringSplit(*itProp, ':');

		//trim the result
		for(std::vector<std::string>::iterator itKV = keyAndValue.begin(); itKV<keyAndValue.end(); itKV++) {
			*itKV = stringTrim(*itKV);
		}
		if(keyAndValue.size() == 2) {
			std::string key = stringToLower(keyAndValue[0]);
			//std::string value = stringToLower(keyAndValue[1]);
			std::string value = keyAndValue[1];

			//remove eventual space between number and pixel / %
			value = stringReplace(value, "  ", " ");
			value = stringReplace(value, " px", "px");
			value = stringReplace(value, " %", "%");

			//at this point we have address, key and value, so store it for later use
			ret.push_back(CssProperty(key, value));
		} else {
			debug::warning("CSS ERROR near "+keyAndValue[0]);
		}
	}
	return ret;
}

void Css::setCssBlock(std::string block) {
	std::vector<CssProperty> props = parseCssBlock(block);
	for(CssProperty& prop: props) {
		applyCssProperty(prop);
	}
}

void Css::applyCssProperty(std::string key, std::string value) {
	CssProperty prop(key, value);
	applyCssProperty(prop);
}

void Css::applyCssProperty(CssProperty& p) {
	if(!isCssDirty)
		return;

	if (parserFunctions.find(p.key) == parserFunctions.end() ) {
		debug::warning("CSS unknown property: "+p.key);
		return;
	}
	parserFunctions[p.key](p.key, p.value);
}


void Css::applyCss() {
	if(!addressable) {
		debug::warning("Css needs Addressable to apply properties");
		return;
	}

	if(propertiesOrder.size() == 0)
		return;

	//if(!isCssDirty)
	//	return;

	//apply CSS style to self and children found by addresses stored in the property list
	for(string& propId: propertiesOrder) {
		std::vector<Addressable*> addressables = addressable->findByAddress(propId);
		for(Addressable* addressable: addressables) {
			if(addressable->components->hasComponent<Css>()) {
				Css* cssChild = addressable->components->getComponent<Css>();
				for(CssProperty& prop: properties[propId]) {
					cssChild->applyCssProperty(prop);
				}
			}
		}
	}

	setCssDirty(false, true);

	//send the css applied event to all children
	cssApplyed(this);

	//TODO: check if this is a good solution
	if(stack) {
		for(Css* cssChild: stack->getChildrenComponents<Css>(true)) {
			cssChild->cssApplyed(cssChild);
		}

		/*
		for(Stack* child:stack->getChildrenRecursive()){
			if(child->components->hasComponent<Css>()){
				Css* childCss
				child->components->getComponent<Css>()
			}
		}
		*/
	}
}

void Css::addCssParserFunction(std::string key, std::function<void(std::string, std::string)> func) {
	parserFunctions[key] = func;
}

void Css::setCssDirty(bool state, bool recursive) {
	isCssDirty = state;

	if(!recursive)
		return;

	if(stack) {
		for(Stack::ChildrenIterator it = stack->childrenBegin(); it<stack->childrenEnd(); it++) {
			if((*it)->components->hasComponent<Css>()) {
				(*it)->components->getComponent<Css>()->setCssDirty(state, true);
			}
		}
	}
}

/*

bool Css::hasCssProperty(string propertyName) {
	return properties.find(propertyName) != properties.end();
}

bool Css::searchParentsForCssProperty(CssProperty& prop) {
	if(stack) {
		Stack* parent = stack;
		while(parent->hasParent()) {
			if(parent->components->hasComponent<Css>()) {
				Css* parentCss = parent->components->getComponent<Css>();
				if(parentCss->hasCssProperty(prop.key)) {
					prop.value = parentCss->properties[prop.key];
				}
			}
			parent = parent->getParent();
		}
	}
}
*/

//**************** STACK
void Css::onStack(Stack* s) {
	stack = s;
	stack->childAdded.connect<Css, &Css::onChildAdded>(this);
}

void Css::onChildAdded(Stack* stack) {
	applyCss(); //TODO: this will overwrite manually set styles

	//TODO: keep cached list of css styles per child for performance reasons
	Stack* parent = stack;
	while(parent->hasParent()) {
		parent = parent->getParent();
		if(parent != NULL && parent->components->hasComponent<Css>()) {
			parent->components->getComponent<Css>()->applyCss();
		}
	}
}

//**************** ADDRESSABLE
void Css::onAddressable(Addressable* addr) {
	addressable = addr;
	addressable->classAdded.connect<Css, &Css::onClassAdded>(this);
	addressable->classRemoved.connect<Css, &Css::onClassRemoved>(this);
}

void Css::onClassAdded(string className) {
	setCssDirty(true, true);
	if(stack) {
		Stack* parent = stack;
		while(parent->hasParent()) {
			parent = parent->getParent();
			if(parent != NULL && parent->components->hasComponent<Css>()) {
				parent->components->getComponent<Css>()->applyCss();
			}
		}
	}
	applyCss();
}

void Css::onClassRemoved(string className) {
	setCssDirty(true, true);
	if(stack) {
		Stack* parent = stack;
		while(parent->hasParent()) {
			parent = parent->getParent();
			if(parent != NULL && parent->components->hasComponent<Css>()) {
				parent->components->getComponent<Css>()->applyCss();
			}
		}
	}
	applyCss();
}

//**************** SERIALIZER
void Css::onSerializer(Serializer* ser) {
	ser->deserialized.connect<Css, &Css::onDeserialize>(this);
	ser->serialized.connect<Css, &Css::onSerialize>(this);
}

void Css::onSerialize(core::VariantList& variants) {

}

void Css::onDeserialize(core::VariantList& variants) {
	if(variants.hasKey("css")) {
		loadCss(variants.get("css"));
	}
}

void Css::getInfo(core::Component::Info& info) {

}
