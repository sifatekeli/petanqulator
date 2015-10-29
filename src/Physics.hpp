
#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "Utils.hpp"

#include <btBulletDynamicsCommon.h>

class Physics;

class PhysicsGround
{
    private:
        btStaticPlaneShape _shape;
        btDefaultMotionState _motionState;
        btRigidBody::btRigidBodyConstructionInfo _constructionInfo;
        btRigidBody _rigidBody;

    public:
        PhysicsGround(btDiscreteDynamicsWorld & world);
};

class PhysicsBall
{
    private:
        btSphereShape _shape;
        btDefaultMotionState _motionState;
        btScalar _mass;
        btVector3 _inertia;
        btRigidBody::btRigidBodyConstructionInfo _constructionInfo;
        btRigidBody _rigidBody;

    public:
        PhysicsBall(btDiscreteDynamicsWorld & world);
        btTransform getTransform();
};

class Physics
{
    private:
        btDbvtBroadphase _broadphase;
        btDefaultCollisionConfiguration _configuration;
        btCollisionDispatcher _dispatcher;
        btSequentialImpulseConstraintSolver _solver;
        btDiscreteDynamicsWorld _world;

        PhysicsGround _ground;
        PhysicsBall _ball;

        bool _isComputing;

    public:
        Physics();
        bool isSimulationRunning() const;
        void computeSimulation(real duration);
};

#endif

