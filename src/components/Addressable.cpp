#include "Addressable.h"
#include "core/Utils.h"

using namespace boxModel::components;
using namespace boxModel::core;

Addressable::Addressable() {
	id = "";
	unaddressable = false;
}

std::string Addressable::getName(){
	return "addressable";
}

void Addressable::setup() {
	//assert(componentContainer->hasComponent<Stackable<Addressable>>());
	LISTEN_FOR_COMPONENT(Serializer, Addressable, onSerializer)
}


bool Addressable::isType(std::string t) {
	return getType() == t;
}

void Addressable::setType(std::string t) {
	type = t;
}

std::vector<std::string> Addressable::getClasses() {
	return classes;
}

void Addressable::setId(std::string str) {
	str = stringTrim(str);
	if(str == id)
		return;
	/* //TODO: warn about duplicate IDs
	if(str.size() == 0) {
		if(id.size()>0)
			idsTaken.erase(std::remove(idsTaken.begin(), idsTaken.end(), str), idsTaken.end());
		return;
	}
	if(std::find(idsTaken.begin(), idsTaken.end(), str)!=idsTaken.end())
		debug::warning("duplicate ID: "+str);
	else
		idsTaken.push_back(str);
	*/
	id = str;
}

std::string Addressable::getId() {
	return id;
}

bool Addressable::isId(std::string idName) {
	return id == idName;
}

bool Addressable::hasId() {
	return id != "";
}

bool Addressable::hasClass(std::string className) {
	return (std::find(classes.begin(), classes.end(), className) != classes.end());
}

void Addressable::addClass(std::string className) {
	classes.push_back(className);
}

void Addressable::addClasses(std::vector<std::string> classNames) {
	classes.insert(classes.end(), classNames.begin(), classNames.end());
}

void Addressable::setClasses(std::vector<std::string> classNames) {
	classes = classNames;
}

void Addressable::removeClass(std::string className) {
	classes.erase(std::remove(classes.begin(), classes.end(), className), classes.end());
}


std::vector<Addressable*> Addressable::findByAddress(std::string path) {
	//prepare return vector
	std::vector<Addressable*> ret;

	//check for Stackable
	if(!components->hasComponent<Stack>()) {
		componentDependencyWarning("Addressable::findByAddress", "Stackable");
		return ret;
	}

	//split the string into address fragments
	std::vector<std::string> pathSplitted = stringSplit(path);


	//store temporary candidates for return
	std::vector<Addressable*> curRet;
	curRet.push_back(this);

	//go through the path
	for(std::vector<std::string>::iterator itPath = pathSplitted.begin(); itPath < pathSplitted.end(); itPath++) {
		std::string item = stringTrim(*itPath);

		std::vector<Addressable*> tmp;

		//check for class id or item
		if(item.size()>0) {
			char begin = item[0];
			switch(begin) {
			case '.':
				item.erase(0,1);
				for(Addressable* addr: curRet) {
					std::vector<Addressable*> t = findByClass(item, addr, (itPath != pathSplitted.begin()));
					tmp.insert(tmp.end(), t.begin(), t.end());
				}
				break;

			case '#':
				item.erase(0,1);
				for(Addressable* addr: curRet) {
					std::vector<Addressable*> t = findById(item, addr, (itPath != pathSplitted.begin()));
					tmp.insert(tmp.end(), t.begin(), t.end());
				}
				break;
			default:
				for(Addressable* addr: curRet) {
					
					bool hasClass = false;
					string className;
					std::vector<std::string> typeSplitted = stringSplit(item, '.');
					if(typeSplitted.size() >= 2){
						item = typeSplitted[0];
						className = typeSplitted[1];
						hasClass = true;
					}
					
					std::vector<Addressable*> t = findByType(item, addr, (itPath != pathSplitted.begin()));
					
					if(hasClass){
						for(Addressable* a: t){
							if(a->hasClass(className)){
								tmp.push_back(a);
							}
						}
					}else{
						tmp.insert(tmp.end(), t.begin(), t.end());
					}
				}
				break;
			}
		}
		//push current items into curRet;
		curRet = tmp;

		if(itPath == pathSplitted.end()-1)
			ret = curRet;
	}

	//remove duplicates
	sort( ret.begin(), ret.end() );
	ret.erase( unique( ret.begin(), ret.end() ), ret.end() );

	return ret;
}

std::vector<ComponentContainer*> Addressable::findContainerByAddress(std::string path) {
	std::vector<ComponentContainer*> ret;
	for(Addressable* addr: findByAddress(path)) {
		ret.push_back(addr->components);
	}
	return ret;
}


std::vector<Addressable*> Addressable::findByClass(std::string className, Addressable* root, bool skipRoot) {
	std::vector<Addressable*> ret;
	if(!skipRoot && root->unaddressable == false && root->hasClass(className)) {
		ret.push_back(root);
	}

	Stack* stack = root->components->getComponent<Stack>();

	for(Stack* stackChild: stack->getChildren()) {
		if(stackChild->components->hasComponent<Addressable>()) {
			std::vector<Addressable*> v = findByClass(className, stackChild->components->getComponent<Addressable>());
			ret.insert( ret.end(), v.begin(), v.end() );
		}
	}

	return ret;
}

std::vector<Addressable*> Addressable::findById(std::string idName, Addressable* root, bool skipRoot) {
	std::vector<Addressable*> ret;
	if(!skipRoot && root->unaddressable == false && root->isId(idName)) {
		ret.push_back(root);
	}

	Stack* stack = root->components->getComponent<Stack>();

	for(Stack* stackChild: stack->getChildren()) {
		if(stackChild->components->hasComponent<Addressable>()) {
			std::vector<Addressable*> v = findById(idName, stackChild->components->getComponent<Addressable>());
			ret.insert( ret.end(), v.begin(), v.end() );
		}
	}

	return ret;
}

std::vector<Addressable*> Addressable::findByType(std::string typeName, Addressable* root, bool skipRoot) {
	std::vector<Addressable*> ret;
	if(!skipRoot && root->unaddressable == false && root->isType(typeName)) {
		ret.push_back(root);
	}

	Stack* stack = root->components->getComponent<Stack>();

	for(Stack* stackChild: stack->getChildren()) {
		if(stackChild->components->hasComponent<Addressable>()) {
			std::vector<Addressable*> v = findByType(typeName, stackChild->components->getComponent<Addressable>());
			ret.insert( ret.end(), v.begin(), v.end() );
		}
	}

	return ret;
}

void Addressable::copyFrom(Addressable* addr) {
	setType(addr->getType());
	setClasses(addr->getClasses());

	if(addr->hasId())
		setId(addr->getId());
}

/************************** SERIALIZING ***********************************************/

void Addressable::onSerializer(Serializer* ser) {
	ser->deserialized.connect<Addressable, &Addressable::onDeserialize>(this);
	ser->serialized.connect<Addressable, &Addressable::onSerialize>(this);
}

void Addressable::onSerialize(VariantList& variants) {
	if(hasId())
		variants.set("id", getId());
	if(classes.size()>0)
		variants.set("class", Variant(classes));
}

void Addressable::onDeserialize(VariantList& variants) {
	if(variants.hasKey("class")) {
		addClasses(variants.get("class").asStringList());
	}
	if(variants.hasKey("id")) {
		setId(variants.get("id"));
	}
}

void Addressable::getInfo(core::Component::Info& info){
	if(classes.size() == 0)
		info["classes"] = "-";
	else
		info["classes"] = core::toString(classes);

	info["id"] = id;
}
