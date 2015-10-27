
#include "Force.hpp"

Viscosity::Viscosity(float viscosity):
    _viscosity(viscosity)
{}

vec3 Viscosity::computeForce(Object & object)
{
    return -(object._velocity * _viscosity * object.getVolume());
}

Gravity::Gravity(float x, float y, float z):
    _gravity(x, y, z)
{}

vec3 Gravity::computeForce(Object &)
{
    return _gravity;
}


