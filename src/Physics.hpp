
#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "GameObject.hpp"
#include "Utils.hpp"

#include <btBulletDynamicsCommon.h>

template <typename T>
class PhysicsObject
{
    private:
        T _shape;
        btScalar _mass;
        btVector3 _inertia;
        btDefaultMotionState _motionState;
        btRigidBody::btRigidBodyConstructionInfo _constructionInfo;
        btRigidBody _rigidBody;
        GameBall * _ptrBall;

    public:
        PhysicsObject(btDiscreteDynamicsWorld & world, const T & shape, 
                btScalar mass, const btVector3 & inertia,
                const btTransform & transform, GameBall * ptrBall):
            _shape(shape),
            _mass(mass),
            _inertia(inertia),
            _motionState(transform),
            _constructionInfo(_mass, &_motionState, &_shape, _inertia),
            _rigidBody(_constructionInfo),
            _ptrBall(ptrBall)
    {
        _shape.calculateLocalInertia(_mass, _inertia);
        _rigidBody.setRestitution(0.7);
        world.addRigidBody(&_rigidBody);
    }

        void updateBall()
        {
            if (_ptrBall)
            {
                btTransform transformation;
                _rigidBody.getMotionState()->getWorldTransform(transformation);
                _ptrBall->_position = transformation.getOrigin();
            }
        }

        const GameBall * getPtrBall() const
        {
            return _ptrBall;
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
        PhysicsObject<btSphereShape> _ballObject;

        bool _isComputing;

    public:
        Physics(GameBall * ptrBall);
        bool isSimulationRunning() const;
        void computeSimulation(real duration);
};

#endif

