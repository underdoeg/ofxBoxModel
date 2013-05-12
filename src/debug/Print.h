#ifndef PRINT_H
#define PRINT_H

#include <string>

namespace ofx
{

namespace boxModel
{

namespace debug
{

void notice(std::string msg);
void warning(std::string msg);
void error(std::string msg);

}

}

}

#endif // PRINT_H
