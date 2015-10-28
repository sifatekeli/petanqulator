
#include "Utils.hpp"

double degToRad(double degAngle)
{
    constexpr double k = M_PI / 180.0;
    return degAngle * k;
}

