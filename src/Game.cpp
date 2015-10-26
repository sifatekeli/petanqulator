
#include "Game.hpp"

Game::Game()
{
    newGame();
}

void Game::newGame()
{
    _remainingBalls = {3, 3};
    _teamOfPlayers = {1, 2};
    _currentPlayer = 1;

    // TODO init ground
    _physics._ground._player = 0;
    _physics._ground._mass = INFINITY;
    _physics._ground._position = {0, 0, 0};
    _physics._ground._velocity = {0, 0, 0};
    _physics._ground._xMin = -10;
    _physics._ground._xMax = 10;
    _physics._ground._zMin = -6;
    _physics._ground._zMax = 6;
    _physics._ground._damping = 0.05;

    _physics._balls.clear();
    Ball jack;
    jack._player = 0;
    jack._mass = 0.05;
    // TODO init jack at a random position
    jack._position = {0,1,0};
    jack._velocity = {0,0,0};
    jack._radius = 0.1;
    _physics._balls.push_back(jack);
}

bool Game::isGameFinished() const
{
    return _remainingBalls[0] == 0 and _remainingBalls[1] == 0;
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

