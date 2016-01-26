// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <btBulletDynamicsCommon.h>

double degToRad(double degAngle);

#include <iostream>

#define UTILS_ERROR(msg) \
{ \
    std::cerr << "error: " << msg  \
        << " (" << __FILE__ << ' ' << __LINE__ << ")" << std::endl; \
    exit(-1); \
} 

#define UTILS_INFO(msg) \
{ \
    std::clog << "info: " << msg  \
        << " (" << __FILE__ << ' ' << __LINE__ << ")" << std::endl; \
} 

#endif
