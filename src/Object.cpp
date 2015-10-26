
#include "Object.hpp"

float Ball::getVolume() const
{
    return 4 * M_PI * _radius * _radius * _radius / 3.f;
}

float Ground::getVolume() const
{
    return INFINITY;
}
