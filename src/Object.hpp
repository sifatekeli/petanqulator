
#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "Utils.hpp"

struct Object 
{
    int _player;
    float _mass;
    vec3 _position;
    vec3 _velocity;
    ~Object() {}
    virtual float getVolume() const = 0;
};

struct Ball : Object
{
    float _radius;
    float getVolume() const;
};

struct Ground : Object
{
    float _xMin;
    float _xMax;
    float _zMin;
    float _zMax;
    float _damping;
    float getVolume() const;
};

#endif

