// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include "Utils.hpp"

struct GameBall
{
    btTransform _transform;
    btVector3 _velocity;
    btScalar _mass;
    btScalar _radius;
    const btVector3 & getPosition() const;
};

struct GameGround
{
    btScalar _xMin, _xMax, _zMin, _zMax;
};

#endif
