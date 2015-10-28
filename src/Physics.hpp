
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
        double _motionThreshold;

    public:
        // compute simulation step by step 
        void startSimulation();
        bool isSimulationRunning() const;
        void computeSimulation(double duration);

    private:
        // compute all collisions at current time
        void computeCollisions();

        // compute elastic collision between two balls
        // do not test contact
        void computeBounce(Ball & ball1, Ball & ball2) const;

        // compute elastic collision between a ball and the ground
        // do not test contact
        void computeBounce(Ball & ball, Ground & ground) const;
};

#endif

