
#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include "Utils.hpp"

struct GameBall 
{
    // TODO btTransform
    vec3 _position;
    real _mass;
    real _radius;
};

struct GameGround 
{
    real _xMin, _xMax, _yMin, _yMax;
};

#endif 

