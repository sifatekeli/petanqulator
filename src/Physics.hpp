
#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include "Force.hpp"
#include "Object.hpp"

#include <memory>
#include <vector>

class Physics
{
    private:
        bool _isComputing;

    public:
        std::vector<Ball> _balls;
        std::vector<std::unique_ptr<Force>> _uptrForces;
        Ground _ground;
        float _velocityThreshold;

    public:
        // compute simulation step by step 
        void startSimulation();
        bool isSimulationFinished();
        void computeSimulation(float duration);

    private:
        // compute all collisions at current time
        void computeCollisions();

        // compute elastic collision between two balls
        // do not test contact
        void computeCollision(Ball & ball1, Ball & ball2) const;

        // compute elastic collision between a ball and the ground
        // do not test contact
        void computeCollision(Ball & ball, Ground & ground) const;
};

#endif

