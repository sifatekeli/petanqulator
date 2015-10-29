
#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include <memory>
#include <vector>

class Physics
{
    private:
        bool _isComputing;

    public:
        // compute simulation step by step 
        void startSimulation();
        bool isSimulationRunning() const;
        void computeSimulation(double duration);
};

#endif

