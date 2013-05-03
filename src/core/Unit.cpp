#include "Unit.h"

namespace ofx
{

namespace boxModel
{

namespace core
{

ostream& operator<<(ostream& os, Unit& unit)
{
    os << unit.getValue();
    return os;
}


}

}

}

