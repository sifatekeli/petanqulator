
// g++ -O2 -g -std=c++11 `pkg-config --cflags --libs bullet` test_bullet.cpp
// valgrind --leak-check=full --show-leak-kinds=all ./a.out

#include <iostream>
#include <btBulletDynamicsCommon.h>

int main (void)
{
    btDbvtBroadphase broadphase;

    btDefaultCollisionConfiguration collisionConfiguration;

    btCollisionDispatcher dispatcher(&collisionConfiguration);

    btSequentialImpulseConstraintSolver solver;

    btDiscreteDynamicsWorld dynamicsWorld (&dispatcher, &broadphase, &solver, 
            &collisionConfiguration);

    dynamicsWorld.setGravity(btVector3(0, -10, 0));

    btStaticPlaneShape groundShape(btVector3(0, 1, 0), 1);

    btSphereShape fallShape(1);

    btDefaultMotionState groundMotionState (
            btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));

    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
            0, &groundMotionState, &groundShape, btVector3(0, 0, 0));

    btRigidBody groundRigidBody (groundRigidBodyCI);

    dynamicsWorld.addRigidBody(&groundRigidBody);

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

    return 0;
}

