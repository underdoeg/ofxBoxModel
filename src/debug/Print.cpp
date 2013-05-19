#include "Print.h"

#include "ofMain.h"

namespace boxModel
{

namespace debug
{

void notice(std::string msg)
{
	ofLogNotice("ofxBoxModel") << msg;
}
	
void error(std::string msg)
{
	ofLogError("ofxBoxModel") << msg;
}
	
void warning(std::string msg)
{
	ofLogWarning("ofxBoxModel") << msg;
}


}

}


