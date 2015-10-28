
#include "Game.hpp"

Game::Game()
{}

void Game::newGame()
{
    // players and teams
    _remainingBallsRed = 6;
    _remainingBallsBlue = 6;
    _currentPlayer = PLAYER_RED;
    _opponentPlayer = PLAYER_BLUE;

    // physics
    _physics._motionThreshold = 1e-9;
    _timeStep = 1e-4;

    // forces
    _physics._uptrForces.clear();
    _physics._uptrForces.emplace_back(new Gravity(0, -9.8f, 0));
    _physics._uptrForces.emplace_back(new Viscosity(20));

    // ground
    _physics._ground = Ground(PLAYER_NONE, INFINITY, vec3(0,0,0), 
            vec3(0,0,0), -10, 10, -6, 6, 0.5);

    // jack
    _physics._balls.clear();
    // TODO init jack at a random position
    _physics._balls.emplace_back(
            PLAYER_JACK, 1, vec3(0,5,0), vec3(0,0,0), 0.1);

    // TODO test
    _physics._balls.emplace_back(
            PLAYER_RED, 5, vec3(1,1,0), vec3(0,0,0), 0.1);
    _physics._balls.emplace_back(
            PLAYER_BLUE, 5, vec3(-1,1,0), vec3(2,0,0), 0.1);
}

bool Game::isGameFinished() const
{
    return _remainingBallsBlue == 0 and _remainingBallsRed == 0;
}

player_t Game::getCurrentPlayer() const
{
    return _currentPlayer;
}

void Game::getBestPlayerStats(player_t & player, int & nbBalls) const
{
    // TODO getBestPlayerStats
    player = PLAYER_RED;
    nbBalls = 0;
}

void Game::throwBall()
{
    // TODO throw ball

    _physics.startSimulation();
    while (_physics.isSimulationRunning())
        _physics.computeSimulation(_timeStep);
}

void Game::interactiveThrowStart()
{
    // TODO throw ball

    _physics.startSimulation();
}

bool Game::interactiveThrowRunning() const
{
    return _physics.isSimulationRunning();
}

void Game::interactiveThrowContinue(double duration)
{
    double t = duration;
    while (t - _timeStep > 0 and interactiveThrowRunning())
    {
        _physics.computeSimulation(_timeStep);
        t -= _timeStep;
    }
    if (t > 1e-4 and interactiveThrowRunning())
        _physics.computeSimulation(t);
}

const Ground & Game::getGround() const
{
    return _physics._ground;
}

const std::vector<Ball> & Game::getBalls() const
{
    return _physics._balls;
}

