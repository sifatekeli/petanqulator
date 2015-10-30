
#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include "Utils.hpp"

struct GameBall 
{
    btTransform _transform;
    btVector3 _velocity;
    btScalar _mass;
    btScalar _radius;
};

struct GameGround 
{
    btScalar _xMin, _xMax, _yMin, _yMax;
};

#endif 

