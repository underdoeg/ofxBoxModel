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

/** is base of implementation **/
template <typename B, typename D>
struct is_base_of // check if B is a base of D
{
    typedef char yes[1];
    typedef char no[2];

    static yes& test(B*);
    static no& test(...);

    static D* get(void);

    static const bool value = sizeof(test(get())) == sizeof(yes);
};

// really basic
template <bool>
struct custom_static_assert;

template <>
struct custom_static_assert<true> {}; // only true is defined

#define STATIC_ASSERT(x) custom_static_assert<(x)>()



/****************************************************************************/
/* STRING STUFF																*/
/****************************************************************************/

std::string stringTrim(std::string &s);

std::vector<std::string> stringSplit(const std::string &in, char delimiter = ' ');

std::string stringReplace(std::string &s, std::string toReplace, std::string replaceWith);

std::string stringRemoveLineBreaks(std::string);

}

}

}

#endif // UTILS_H
