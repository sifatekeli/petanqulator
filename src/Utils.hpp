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
