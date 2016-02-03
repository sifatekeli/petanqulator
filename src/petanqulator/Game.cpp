// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Game.hpp"

#include <algorithm>
#include <sstream>

Game::Game():
    _engine(std::random_device{}()),
    _distribution(-4, 4),
    _currentPlayer{PLAYER_RED},
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

GameResult Game::computeResult() const
{
    if (_redBalls.empty() and _blueBalls.empty())
        return {PLAYER_NONE, 0, {}};

    GameResult res;

    // get jack
    const GameBall & jack = getJack();
    btVector3 jackPos = jack._transform.getOrigin();

    // compute ball results (distance from jack)
    auto distanceFun = [&jackPos] (const GameBall & b, player_t p)
    {
        btVector3 bPos = b._transform.getOrigin();
        btVector3 v = bPos - jackPos;
        return BallResult{p, v.length2(), false};
    };
    std::transform(_redBalls.begin(), _redBalls.end(), 
            std::back_inserter(res._ballResults), 
            std::bind(distanceFun, std::placeholders::_1, PLAYER_RED));
    std::transform(_blueBalls.begin(), _blueBalls.end(), 
            std::back_inserter(res._ballResults), 
            std::bind(distanceFun, std::placeholders::_1, PLAYER_BLUE));
    assert(not res._ballResults.empty());

    // sort balls by distance from jack
    auto cmpFun = [] (const BallResult & b1, const BallResult & b2)
    { return b1._distance < b2._distance; };
    std::sort(res._ballResults.begin(), res._ballResults.end(), cmpFun);

    // find winning balls
    res._winningPlayer = res._ballResults.front()._player;
    res._nbWinningBalls = 0;
    for (BallResult & b : res._ballResults) 
    {
        if (b._player == res._winningPlayer) 
        {
            b._isWinning = true;
            res._nbWinningBalls++;
        }
        else break;
    }

    return res;
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

    // TODO clamp vx vy vz

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
        GameResult res = computeResult();
        _currentPlayer = 
            res._winningPlayer == PLAYER_RED ? PLAYER_BLUE : PLAYER_RED;
    }
}

