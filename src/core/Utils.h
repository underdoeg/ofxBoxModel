#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <sstream>


namespace ofx {

namespace boxModel {

namespace core {

/* * * * *
 * Utility functions for the The Curiously Recurring Template Pattern and Mixins
 *
 * No idea if the pattern will work out
 *
 * Some info here: 	http://eli.thegreenplace.net/2011/05/17/the-curiously-recurring-template-pattern-in-c/
 * 					http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 * 					http://stackoverflow.com/questions/3779489/parallel-inheritance-trees-where-classes-from-one-tree-have-containers-of-class
 * 					https://bitbucket.org/rdpate/kniht/src/e039d5310edd/kniht/crtp.hxx#cl-55
 * * * * */

template <class Type, class Derived>
Derived* crtpSelfPtr(Type* ptr) {
	return static_cast<Derived*>(ptr);
};

template <class Type, class Derived>
Derived& crtpSelf(Type& t) {
	return static_cast<Derived&>(t);
};

/****************************************************************************/
/*      STUFF																*/
/****************************************************************************/

std::string trimString(std::string &s);

std::vector<std::string> splitString(const std::string &in, char delimiter = ' ');

}

}

}

#endif // UTILS_H