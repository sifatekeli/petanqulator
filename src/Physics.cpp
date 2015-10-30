
#include "Physics.hpp"
#include "Utils.hpp"

Physics::Physics(GameBall * ptrBall):
    _broadphase(),
    _configuration(),
    _dispatcher(&_configuration),
    _solver(),
    _world(&_dispatcher, &_broadphase, &_solver, &_configuration),
    _groundObject(_world, btStaticPlaneShape(btVector3(0, 0, 1), 0),
            0, 
            btTransform(btQuaternion(0,0,0,1), btVector3(0,0,0)),
            nullptr),
    _ballObject(_world, btSphereShape(1),
            1, 
            btTransform(btQuaternion(0,0,0,1), btVector3(0,0,4)),
            ptrBall)
{
    _world.setGravity(btVector3(0, 0, -10));
    _isComputing = true;
}

bool Physics::isSimulationRunning() const
{
    return _isComputing;
}

void Physics::computeSimulation(real duration)
{
    _world.stepSimulation(0.1*duration, 100);

    // TODO vector of balls
    _ballObject.updateBall();

    // TODO remove balls outside limits
    
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

