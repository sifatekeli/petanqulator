
#include "Game.hpp"

Game::Game()
{
    newGame();
}

void Game::newGame()
{
    // players and teams
    _remainingBalls = {3, 3};
    _teamOfPlayers = {1, 2};
    _currentPlayer = 1;

    // physics
    _physics._motionThreshold = 1e-4;

    // forces
    _physics._uptrForces.clear();
    _physics._uptrForces.emplace_back(new Gravity(0, -9.8f, 0));
    _physics._uptrForces.emplace_back(new Viscosity(20));

    // ground
    _physics._ground = 
        Ground(0, INFINITY, vec3(0,0,0), vec3(0,0,0), -10, 10, -6, 6, 0.4);

    // jack
    _physics._balls.clear();
    // TODO init jack at a random position
    _physics._balls.emplace_back(0, 0.01, vec3(0,1,0), vec3(0,0,0), 0.1);

    // TODO test
    _physics._balls.emplace_back(1, 0.05, vec3(1,1,0), vec3(0,0,0), 0.1);
    _physics._balls.emplace_back(2, 0.05, vec3(-1,1,0), vec3(0,0,0), 0.1);
}

bool Game::isGameFinished() const
{
    return std::all_of(_remainingBalls.begin(), _remainingBalls.end(), 
            [](int n) {return n==0;});
}

int Game::getCurrentPlayer() const
{
    return _currentPlayer;
}

void Game::getBestPlayerStats(int & team, int & nbBalls) const
{
    // TODO getBestPlayerStats
    team = 1;
    nbBalls = 0;
}

void Game::throwBall()
{
    // TODO throwBall

    _physics.startSimulation();
    while (not _physics.isSimulationFinished())
        _physics.computeSimulation(0.01);
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

const std::vector<int> & Game::getTeamOfPlayers() const
{
    return _teamOfPlayers;
}

