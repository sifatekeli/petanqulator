
#include "GameObject.hpp"


const btVector3 & GameBall::getPosition() const
{
    return _transform.getOrigin();
}

