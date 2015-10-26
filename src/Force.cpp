
#include "Force.hpp"

vec3 Viscosity::computeForce(Object & object)
{
    return -(object._velocity * _viscosity * object.getVolume());
}

vec3 Gravity::computeForce(Object &)
{
    return _gravity;
}


