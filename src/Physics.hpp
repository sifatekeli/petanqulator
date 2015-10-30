
#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "GameObject.hpp"

#include <btBulletDynamicsCommon.h>
#include <list>

template <typename T>
class PhysicsObject
{
    private:
        // TODO use one shape for multiple collision objects
        T _shape;
        btDefaultMotionState _motionState;
        btRigidBody _rigidBody;
        GameBall * _ptrBall;

    public:
        PhysicsObject(btDiscreteDynamicsWorld & world, const T & shape, 
                btScalar mass, btVector3 velocity,
                const btTransform & transform, 
                GameBall * ptrBall):
            _shape(shape),
            _motionState(transform),
            _rigidBody(mass, &_motionState, &_shape),
            _ptrBall(ptrBall)
    {
        // TODO angular velocity ?
        _rigidBody.setLinearVelocity(velocity);
        _rigidBody.setDamping(0.1, 0.1);
        _rigidBody.setRestitution(0.7);
        _rigidBody.setFriction(0.1);
        // TODO _rigidBody.setRollingFriction(0.01);
        world.addRigidBody(&_rigidBody);
    }

        void updateBall()
        {
            if (_ptrBall)
                // TODO use _motionState ?
                _rigidBody.getMotionState()->getWorldTransform(
                        _ptrBall->_transform);
        }
};

class Physics
{
    private:
        btDbvtBroadphase _broadphase;
        btDefaultCollisionConfiguration _configuration;
        btCollisionDispatcher _dispatcher;
        btSequentialImpulseConstraintSolver _solver;
        btDiscreteDynamicsWorld _world;

        PhysicsObject<btStaticPlaneShape> _groundObject;

        // TODO vector
        std::list<PhysicsObject<btSphereShape>> _ballObjects;

        bool _isComputing;

    public:
        Physics();
        void addBall(GameBall * ptrBall);
        bool isSimulationRunning() const;
        void computeSimulation(btScalar duration);
};

#endif

