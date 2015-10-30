
#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include "Utils.hpp"

struct GameBall 
{
    vec3 _position;
    vec3 _velocity;
    real _mass;
    real _radius;
};

struct GameGround 
{
    real _xMin, _xMax, _yMin, _yMax;
};

#endif 

