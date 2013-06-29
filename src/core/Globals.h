#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

namespace boxModel {

namespace core {

class Globals {
public:
	static Globals& get();
	std::string dataRoot;
	
private:
	static Globals instance;
	Globals();
	~Globals();
};

}

}

#endif // GLOBALS_H
