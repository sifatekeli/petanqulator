// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Utils.hpp"

double degToRad(double degAngle)
{
    constexpr double k = M_PI / 180.0;
    return degAngle * k;
}

