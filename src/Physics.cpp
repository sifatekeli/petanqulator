
#include "Physics.hpp"
#include "Utils.hpp"

///////////////////////////////////////////////////////////////////////////////
// PhysicsGround
///////////////////////////////////////////////////////////////////////////////

PhysicsGround::PhysicsGround(btDiscreteDynamicsWorld & world):
    _shape(btVector3(0, 1, 0), 1),
    _motionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,-1,0))),
    _constructionInfo(0, &_motionState, &_shape, btVector3(0, 0, 0)),
    _rigidBody(_constructionInfo)
{
    world.addRigidBody(&_rigidBody);
}

///////////////////////////////////////////////////////////////////////////////
// PhysicsBall
///////////////////////////////////////////////////////////////////////////////

PhysicsBall::PhysicsBall(btDiscreteDynamicsWorld & world):
    _shape(1),
    _motionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,50,0))),
    _mass(1),
    _inertia(0, 0, 0),
    _constructionInfo(_mass, &_motionState, &_shape, _inertia),
    _rigidBody(_constructionInfo)
{
    _shape.calculateLocalInertia(_mass, _inertia);
    world.addRigidBody(&_rigidBody);
}

btTransform PhysicsBall::getTransform()
{
    btTransform trans;
    _rigidBody.getMotionState()->getWorldTransform(trans);
}

///////////////////////////////////////////////////////////////////////////////
// Physics
///////////////////////////////////////////////////////////////////////////////

Physics::Physics():
    _broadphase(),
    _configuration(),
    _dispatcher(&_configuration),
    _solver(),
    _world(&_dispatcher, &_broadphase, &_solver, &_configuration),
    _ground(_world),
    _ball(_world)
{

    _world.setGravity(btVector3(0, -10, 0));

    _isComputing = true;

}

bool Physics::isSimulationRunning() const
{
    return _isComputing;
}

void Physics::computeSimulation(real duration)
{

    for (int i = 0; i < 50; i++) {
        _world.stepSimulation(1 / 10.f, 10);
        btTransform trans = _ball.getTransform();
        //std::clog << "sphere height: " << trans.getOrigin().getY() << std::endl;
    }

    _isComputing = false;
}


/*

    // global inits
    btDbvtBroadphase broadphase;
    btDefaultCollisionConfiguration collisionConfiguration;
    btCollisionDispatcher dispatcher(&collisionConfiguration);
    btSequentialImpulseConstraintSolver solver;
    btDiscreteDynamicsWorld dynamicsWorld (&dispatcher, &broadphase, &solver, 
            &collisionConfiguration);
    dynamicsWorld.setGravity(btVector3(0, -10, 0));

    // ground
    btStaticPlaneShape groundShape(btVector3(0, 1, 0), 1);
    btDefaultMotionState groundMotionState (
            btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
            0, &groundMotionState, &groundShape, btVector3(0, 0, 0));
    btRigidBody groundRigidBody (groundRigidBodyCI);
    dynamicsWorld.addRigidBody(&groundRigidBody);

    // sphere
    btSphereShape fallShape(1);
    btDefaultMotionState fallMotionState (
            btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
    btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    fallShape.calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, 
            &fallMotionState, &fallShape, fallInertia);
    btRigidBody fallRigidBody (fallRigidBodyCI);
    dynamicsWorld.addRigidBody(&fallRigidBody);

    for (int i = 0; i < 50; i++) {
        dynamicsWorld.stepSimulation(1 / 10.f, 10);
        btTransform trans;
        fallRigidBody.getMotionState()->getWorldTransform(trans);
        std::clog << "sphere height: " << trans.getOrigin().getY() << std::endl;
    }

    */

