
#include "Physics.hpp"
#include "Utils.hpp"

void Physics::startSimulation()
{
    _isComputing = true;
}

bool Physics::isSimulationRunning() const
{
    return _isComputing;
}

void Physics::computeSimulation(double duration)
{
    _isComputing = false;
}

