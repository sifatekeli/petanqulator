
#include "Physics.hpp"
#include "Utils.hpp"

Physics::Physics(GameGround * ptrGround):
    _broadphase(),
    _configuration(),
    _dispatcher(&_configuration),
    _solver(),
    _world(&_dispatcher, &_broadphase, &_solver, &_configuration),
    // TODO game ground / physics ground
    _groundObject(_world, btStaticPlaneShape(btVector3(0, 0, 1), 0),
            0, btVector3(0, 0, 0),
            btTransform(btQuaternion(0,0,0,1), btVector3(0,0,0)),
            nullptr)
{
    _world.setGravity(btVector3(0, 0, -10));
    _isComputing = true;
}

void Physics::addBall(GameBall * ptrBall)
{
    _ballObjects.emplace_back(_world, btSphereShape(ptrBall->_radius),
            1, ptrBall->_velocity,
            btTransform(btQuaternion(0,0,0,1), ptrBall->_position),
            ptrBall);
    ptrBall->_velocity = btVector3(0, 0, 0);
}

bool Physics::isSimulationRunning() const
{
    return _isComputing;
}

void Physics::computeSimulation(real duration)
{
    _world.stepSimulation(duration);

    for (auto & b : _ballObjects)
        b.updateBall();
    
    // detect end of simulation 
    _isComputing = false;
    for (int i=0; i<_world.getNumCollisionObjects(); i++)
    {
        btCollisionObject * ptrColObj =  _world.getCollisionObjectArray()[i];
        int activationState = ptrColObj->getActivationState();
        if (activationState==ACTIVE_TAG or activationState==WANTS_DEACTIVATION)
        {
            _isComputing = true;
            break;
        }
    }
}

