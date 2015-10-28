
// g++ -O2 -std=c++14 `pkg-config --cflags --libs bullet` test_bullet.cpp 

#include <iostream>
#include <memory>

#include <btBulletDynamicsCommon.h>

int main (void)
{

    std::unique_ptr<btBroadphaseInterface> broadphase 
        = std::make_unique<btDbvtBroadphase>();

    std::unique_ptr<btDefaultCollisionConfiguration> collisionConfiguration 
        = std::make_unique<btDefaultCollisionConfiguration>();

    std::unique_ptr<btCollisionDispatcher> dispatcher 
        = std::make_unique<btCollisionDispatcher>(collisionConfiguration.get());

    std::unique_ptr<btSequentialImpulseConstraintSolver> solver 
        = std::make_unique<btSequentialImpulseConstraintSolver>();

    std::unique_ptr<btDiscreteDynamicsWorld> dynamicsWorld 
        = std::make_unique<btDiscreteDynamicsWorld>(dispatcher.get(),
                broadphase.get(), solver.get(), collisionConfiguration.get());

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    std::unique_ptr<btCollisionShape> groundShape 
        = std::make_unique<btStaticPlaneShape>(btVector3(0, 1, 0), 1);

    std::unique_ptr<btCollisionShape> fallShape 
        = std::make_unique<btSphereShape>(1);

    std::unique_ptr<btDefaultMotionState> groundMotionState 
        = std::make_unique<btDefaultMotionState>(
                btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));

    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
            0, groundMotionState.get(), groundShape.get(), btVector3(0, 0, 0));

    std::unique_ptr<btRigidBody> groundRigidBody 
        = std::make_unique<btRigidBody>(groundRigidBodyCI);

    dynamicsWorld->addRigidBody(groundRigidBody.get());


    std::unique_ptr<btDefaultMotionState> fallMotionState 
        = std::make_unique<btDefaultMotionState>(
                btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));

    btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, 
            fallMotionState.get(), fallShape.get(), fallInertia);
    std::unique_ptr<btRigidBody> fallRigidBody 
        = std::make_unique<btRigidBody>(fallRigidBodyCI);
    dynamicsWorld->addRigidBody(fallRigidBody.get());


    for (int i = 0; i < 300; i++) {
        dynamicsWorld->stepSimulation(1 / 60.f, 10);

        btTransform trans;
        fallRigidBody->getMotionState()->getWorldTransform(trans);

        std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
    }

    dynamicsWorld->removeRigidBody(fallRigidBody.get());
    dynamicsWorld->removeRigidBody(groundRigidBody.get());

    return 0;
}

