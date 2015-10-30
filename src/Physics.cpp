
#include "Physics.hpp"
#include "Utils.hpp"

Physics::Physics(GameBall * ptrBall):
    _broadphase(),
    _configuration(),
    _dispatcher(&_configuration),
    _solver(),
    _world(&_dispatcher, &_broadphase, &_solver, &_configuration),
    _groundObject(_world, btStaticPlaneShape(btVector3(0, 0, -1), 0),
            0, btVector3(0, 0, 0), btTransform(), nullptr),
    _ballObject(_world, btSphereShape(1),
            1, btVector3(0, 0, 0), 
            btTransform(btQuaternion(0,0,0,1), btVector3(0,0,4)),
            ptrBall)
{
    _world.setGravity(btVector3(0, 0, -9));
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
    // TODO
    _isComputing = _ballObject.getPtrBall()->_position.getZ() > -1;
}

