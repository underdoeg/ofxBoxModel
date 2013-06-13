#ifndef UNIT_H
#define UNIT_H


namespace boxModel {

namespace core {

class Unit {
public:

	enum Type {
	    Auto,
	    Pixel,
	    Percent,
		Type_None
	};

	Nano::signal<void(Unit*)> changed;
	Nano::signal<void(float)> valueChanged;
	Nano::signal<void(Type)> typeChanged;
	Nano::signal<void(float)> containerSizeChanged;

	Unit():bSet(false),value(0),type(Pixel) {
	}

	void set(float value, Type type) {
		set(value);
		set(type);
	}

	operator const float & () const {
		return value;
	}

	const float& operator=(float val) {
		set(val);
		return value;
	}

	const Type& operator=(Type t) {
		set(t);
		return type;
	}

	const Unit operator=(Unit t) {
		set(t);
		return t;
	}
	
	const bool operator==(Type t){
		return type == t;
	}
	
	const bool operator==(float v){
		return value == v;
	}

	void set(float val) {

		if(bSet && val == value)
			return;
		bSet = true;
		value = val;
		dispatchChanged();
		valueChanged(value);
	}

	void set(Type t) {
		if(bSet && type == t)
			return;
		bSet = true;
		type = t;
		if(type == 0)
			value = 0;
		dispatchChanged();
		typeChanged(type);
	}

	void set(Unit u) {
		set(u.getType());
		set(u.getValue());
	}

	const float getValue() {
		return value;
	}

	Type getType() {
		return type;
	}

	bool isSet() {
		return bSet;
	}

	float getValueCalculated() {
		return getValueCalculated(containerSize);
	}

	void setContainerSize(float s) {
		if(containerSize == s)
			return;
		containerSize = s;
		if(type == Percent){
			dispatchChanged();
		}
	}

	static Unit parseCssNumber(std::string val) {
		Unit u;
		std::string num = "";
		if(val.rfind("%") != std::string::npos) {
			u = Unit::Percent;
			num = stringTrim(stringReplace(val, "%", ""));
		} else if(val.rfind("px") != std::string::npos) {
			u = Unit::Pixel;
			num = stringTrim(stringReplace(val, "px", ""));
		} else if(val == "auto"){
			u = Unit::Auto;
		} else if(val == "none"){
			u = Unit::Type_None;
		} else {
			u = Unit::Pixel;
			num = val;
		}
		u = stringToFloat(num);
		return u;
	}

	static std::vector<Unit> parseCssNumberBlock(std::string val) {
		std::vector<Unit> ret;
		std::vector<std::string> splitted = stringSplit(val, ' ');
		for(std::vector<std::string>::iterator it = splitted.begin(); it < splitted.end(); it++) {
			ret.push_back(Unit::parseCssNumber(*it));
		}
		if(ret.size()>4)
			debug::warning("CSS number block with more than 4 elements "+val);
		return ret;
	}
private:
	void dispatchChanged() {
		changed(this);
	}

	float getValueCalculated(float parentSize) { //helper function, only for internal use
		if(type == Percent) {
			std::cout << "MY CONTAINER " << parentSize << " --- " << value*.01*parentSize << std::endl;
			return value*.01*parentSize;
		} else if(type == Auto)
			return 0;
		return value;
	}

	bool bSet;
	float value;
	Type type;

	float containerSize;

	friend class BoxModel;
};

class UnitGroup {
public:
	UnitGroup() {
		add(&top);
		add(&bottom);
		add(&left);
		add(&right);
	}

	~UnitGroup() {

	}

	void add(Unit* u) {
		u->changed.connect<UnitGroup, &UnitGroup::onUnitChanged>(this);
		units.push_back(u);
	}

	void set(float value, Unit::Type type) {
		set(value);
		set(type);
	}

	const float operator=(float val) {
		set(val);
		return val;
	}

	const Unit::Type operator=(Unit::Type t) {
		set(t);
		return t;
	}

	const Unit operator=(Unit u) {
		set(u);
		return u;
	}

	void set(float value) {
		for(typename std::vector<Unit*>::iterator it = units.begin(); it < units.end(); it++) {
			(*it)->set(value);
		}
	}

	void set(Unit value) {
		for(typename std::vector<Unit*>::iterator it = units.begin(); it < units.end(); it++) {
			(*it)->set(value);
		}
	}

	void set(Unit::Type type) {
		for(typename std::vector<Unit*>::iterator it = units.begin(); it < units.end(); it++) {
			(*it)->set(type);
		}
	}

	Nano::signal<void(UnitGroup*)> changed;
	Nano::signal<void(Unit*)> unitChanged;

	core::Unit top;
	core::Unit right;
	core::Unit bottom;
	core::Unit left;

private:
	std::vector<Unit*> units;

	void onUnitChanged(Unit* u) {
		changed(this);
		unitChanged(u);
	}
};

}

}

#endif // UNIT_H
