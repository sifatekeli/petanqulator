
#include "Game.hpp"

Game::Game()
{
    newGame();
}

void Game::newGame()
{
    // players and teams
    _remainingBallsRed = 6;
    _remainingBallsBlue = 6;
    _currentPlayer = PLAYER_RED;
    _opponentPlayer = PLAYER_BLUE;

    // physics
    _physics._motionThreshold = 1e-4;
    _timeStep = 1e-2;

    // forces
    _physics._uptrForces.clear();
    _physics._uptrForces.emplace_back(new Gravity(0, -9.8f, 0));
    _physics._uptrForces.emplace_back(new Viscosity(20));

    // ground
    _physics._ground = Ground(PLAYER_NONE, INFINITY, vec3(0,0,0), 
            vec3(0,0,0), -10, 10, -6, 6, 0.4);

    // jack
    _physics._balls.clear();
    // TODO init jack at a random position
    _physics._balls.emplace_back(
            PLAYER_JACK, 0.01, vec3(0,1,0), vec3(0,0,0), 0.1);

    // TODO test
    _physics._balls.emplace_back(
            PLAYER_RED, 0.05, vec3(1,1,0), vec3(0,0,0), 0.1);
    _physics._balls.emplace_back(
            PLAYER_BLUE, 0.05, vec3(-1,1,0), vec3(0,0,0), 0.1);
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
    // TODO throwBall

    _physics.startSimulation();
    while (not _physics.isSimulationFinished())
        _physics.computeSimulation(_timeStep);
}

void Game::interactiveThrowStart()
{
    // TODO interactiveThrowStart
}

bool Game::interactiveThrowFinished() const
{
    // TODO interactiveThrowFinished
    return true;
}

void Game::interactiveThrowContinue()
{
    // TODO interactiveThrowContinue
}

const Ground & Game::getGround() const
{
    return _physics._ground;
}

const std::vector<Ball> & Game::getBalls() const
{
    return _physics._balls;
}

