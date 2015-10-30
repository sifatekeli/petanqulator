
// g++ -O2 -g -std=c++11 `pkg-config --cflags --libs bullet` test_bullet.cpp
// valgrind --leak-check=full --show-leak-kinds=all ./a.out
// ./a.out && octave plot_bullet.m

#include <fstream>
#include <iostream>
#include <btBulletDynamicsCommon.h>

int main (void)
{

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
    groundRigidBody.setRestitution(0.8);
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
    fallRigidBody.setRestitution(0.8);
    dynamicsWorld.addRigidBody(&fallRigidBody);

    // begin octave output
    std::ofstream os("plot_bullet.m");
    os << "graphics_toolkit('gnuplot')\n";
    os << "figure;" << std::endl;
    os << "T=[";

    for (int i = 0; i < 200; i++) {
        dynamicsWorld.stepSimulation(1 / 10.f, 10);
        btTransform trans;
        fallRigidBody.getMotionState()->getWorldTransform(trans);
        //std::clog << "sphere height: " << trans.getOrigin().getY() << std::endl;
        os << trans.getOrigin().getY() << ' ';
    }

    // end octave output
    os << "];" << std::endl;
    os << "plot(T);" << std::endl;
    os << "title(\'T\');" << std::endl;
    os << "pause;" << std::endl;

    return 0;
}

