
#ifndef _FORCE_HPP_
#define _FORCE_HPP_

#include "Object.hpp"

struct Force
{
    virtual ~Force() {}
    virtual vec3 computeForce(Object & object) = 0;
};

struct Viscosity : Force
{
    float _viscosity;
    vec3 computeForce(Object & object);
};

struct Gravity : Force
{
    vec3 _gravity;
    vec3 computeForce(Object & object);
};

#endif

