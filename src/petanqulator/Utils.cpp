// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Utils.hpp"

#include <iomanip>

double degToRad(double degAngle)
{
    constexpr double k = M_PI / 180.0;
    return degAngle * k;
}

double clamp(double x, double xmin, double xmax)
{
    return std::min(xmax, std::max(xmin, x));
}

std::ostream & operator<<(std::ostream & os, const btVector3 & v)
{
    os << '(' << std::setprecision(2) << v.getX() 
        << ", " << std::setprecision(2) << v.getY() 
        << ", " << std::setprecision(2) << v.getZ() << ')';
    return os;
}

