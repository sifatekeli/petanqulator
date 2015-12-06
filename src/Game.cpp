// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Game.hpp"

#include <algorithm>
#include <sstream>

Game::Game():
    _engine(std::random_device()()),
    _distribution(-4, 4),
    _currentPlayer(PLAYER_RED),
    _remainingBallsRed(0),
    _remainingBallsBlue(0)
{}

void Game::newGame()
{
    // players and teams
    _remainingBallsRed = 2;
    _remainingBallsBlue = 2;
    _currentPlayer = PLAYER_RED;
    _shooterPosition = btVector3(-8, 1, 0);

    // ground
    _ground = {-10, 10, -6, 6};

    // jack
    btScalar x = _distribution(_engine);
    btScalar z = _distribution(_engine);
    _jack = {btTransform(btQuaternion(0,0,0,1),btVector3(x,0.2,z)), 
        btVector3(0, 0, 0), 0.1, 0.2};

    _redBalls.clear();
    _blueBalls.clear();
}

bool Game::isGameFinished() const
{
    return _remainingBallsBlue == 0 and _remainingBallsRed == 0;
}

void Game::getBestPlayerStats(player_t & player, int & nbBalls) const
{
    if (_redBalls.empty() and _blueBalls.empty())
    {
        player = PLAYER_NONE;
        nbBalls = 0;
        return;
    }

    // get jack
    const GameBall & jack = getJack();
    btVector3 jackPos = jack._transform.getOrigin();

    // compute red and blue vectors of distances to the jack
    auto distanceFun = [&jackPos] (const GameBall & b)
    {
        btVector3 bPos = b._transform.getOrigin();
        btVector3 v = bPos - jackPos;
        return v.length2();
    };
    std::vector<btScalar> redDists(_redBalls.size());
    std::transform(_redBalls.begin(), _redBalls.end(), redDists.begin(), 
            distanceFun);
    std::vector<btScalar> blueDists(_blueBalls.size());
    std::transform(_blueBalls.begin(), _blueBalls.end(), blueDists.begin(), 
            distanceFun);

    // find minimum distances for red and blue
    btScalar redMin = *std::min_element(redDists.begin(),redDists.end());
    btScalar blueMin = *std::min_element(blueDists.begin(),blueDists.end());

    // count numbers of winning balls
    if (redMin < blueMin)
    {
        player = PLAYER_RED;
        nbBalls = std::count_if(redDists.begin(), redDists.end(), 
                [blueMin] (btScalar d) { return d < blueMin; });
    }
    else
    {
        player = PLAYER_BLUE;
        nbBalls = std::count_if(blueDists.begin(), blueDists.end(), 
                [redMin] (btScalar d) { return d < redMin; });
    }
}

player_t Game::getCurrentPlayer() const
{
    return _currentPlayer;
}

int Game::getRemainingBallsRed() const
{
    return _remainingBallsRed;
}

int Game::getRemainingBallsBlue() const
{
    return _remainingBallsBlue;
}

const std::vector<GameBall> & Game::getRedBalls() const
{
    return _redBalls;
}

const std::vector<GameBall> & Game::getBlueBalls() const
{
    return _blueBalls;
}

const GameGround & Game::getGround() const
{
    return _ground;
}

const GameBall & Game::getJack() const
{
    return _jack;
}

btVector3 Game::getShooterPosition() const
{
    return _shooterPosition;
}

void Game::throwBall(double vx, double vy, double vz)
{
    // create ball
    createBall(vx, vy, vz);

    _uptrPhysics.reset(new Physics);
    _uptrPhysics->addBall(&_jack);
    for (GameBall & b : _redBalls)
        _uptrPhysics->addBall(std::addressof(b));
    for (GameBall & b : _blueBalls)
        _uptrPhysics->addBall(std::addressof(b));
    _uptrPhysics->computeSimulation(0.1);

    // TODO ground limits for physics

    updateCurrentPlayer();
}

void Game::interactiveThrowStart(double vx, double vy, double vz)
{
    // create ball
    createBall(vx, vy, vz);

    // create physics
    _uptrPhysics.reset(new Physics);
    _uptrPhysics->addBall(&_jack);
    for (GameBall & b : _redBalls)
        _uptrPhysics->addBall(std::addressof(b));
    for (GameBall & b : _blueBalls)
        _uptrPhysics->addBall(std::addressof(b));
}

bool Game::interactiveThrowRunning() 
{
    if (_uptrPhysics->isSimulationRunning())
    {
        return true;
    }
    else
    {
        _uptrPhysics.reset();

        // TODO ground limits for physics

        updateCurrentPlayer();
        return false;
    }
}

void Game::interactiveThrowContinue(double duration)
{
    _uptrPhysics->computeSimulation(duration);
}

void Game::createBall(double vx, double vy, double vz)
{
    if (_currentPlayer == PLAYER_NONE)
        return;

    // update game data
    if (_currentPlayer == PLAYER_BLUE)
    {
        _blueBalls.push_back(
                {btTransform(btQuaternion(0,0,0,1),_shooterPosition), 
                btVector3(vx,vy,vz), 0.2, 0.4});
        _remainingBallsBlue--;
    }
    else if (_currentPlayer == PLAYER_RED)
    {
        _redBalls.push_back(
                {btTransform(btQuaternion(0,0,0,1),_shooterPosition), 
                btVector3(vx,vy,vz), 0.2, 0.4});
        _remainingBallsRed--;
    }
}

void Game::updateCurrentPlayer()
{
    if (_redBalls.empty())
        _currentPlayer = PLAYER_RED;
    else if (_blueBalls.empty())
        _currentPlayer = PLAYER_BLUE;
    else if (_remainingBallsBlue == 0 and _remainingBallsRed > 0)
        _currentPlayer = PLAYER_RED;
    else if (_remainingBallsRed == 0 and _remainingBallsBlue > 0)
        _currentPlayer = PLAYER_BLUE;
    else if (_remainingBallsBlue == 0 and _remainingBallsRed == 0)
        _currentPlayer = PLAYER_NONE;
    // if all player can play, find looser
    else
    {
        player_t bestPlayer;
        int nbBalls;
        getBestPlayerStats(bestPlayer, nbBalls);
        _currentPlayer = bestPlayer == PLAYER_RED ? PLAYER_BLUE : PLAYER_RED;
    }
}

