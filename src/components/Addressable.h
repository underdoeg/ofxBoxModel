#ifndef ADDRESSABLE_H
#define ADDRESSABLE_H

#include "core/Utils.h"
#include "core/Component.h"
#include "Serializer.h"
#include "Stack.h"
#include <vector>
#include <string>
#include <algorithm>

namespace boxModel {

namespace components {

class Addressable: public core::Component {
public:
	Addressable();

	void setup();	

	bool isType(std::string Addressable);
	virtual std::string getType(){
		return type;
	}
	void setType(std::string type);

	void setId(std::string str);
	std::string getId();
	bool isId(std::string idName);
	bool hasId();

	std::vector<std::string> getClasses();
	bool hasClass(std::string className);
	void addClass(std::string className);
	void addClasses(std::vector<std::string> classNames);
	void setClasses(std::vector<std::string> classNames);
	void removeClass(std::string className);
	
	template<class Type>
	std::vector<Type*> findByAddress(std::string path){
		std::vector<Type*> ret;
		std::vector<Addressable*> res = findByAddress(path);
		for(std::vector<Addressable*>::iterator it = res.begin(); it<res.end();it++){
			Addressable* item = *it;
			if(core::instanceIsBaseOf<Addressable, Type>(item)){
				ret.push_back(core::castTo<Addressable, Type>(item, false));
			}
		}
		return ret;
	}
	
	void copyFrom(Addressable* addressable);
	
	std::vector<Addressable*> findByAddress(std::string path);

private:
	static std::vector<std::string > idsTaken;

	std::vector<Addressable*> findByClass(std::string className, Addressable* root, bool skipRoot = false);
	std::vector<Addressable*> findById(std::string idName, Addressable* root, bool skipRoot = false);	
	std::vector<Addressable*> findByType(std::string typeName, Addressable* root, bool skipRoot = false);
	
	/************************** SERIALIZING ***********************************************/
	void onSerializer(Serializer* ser);
	void onSerialize(core::VariantList& variants);
	void onDeserialize(core::VariantList& variants);

	std::vector<std::string> classes;
	std::string id;
	std::string type;
};

}

}

#endif // ADDRESSABLE_H
