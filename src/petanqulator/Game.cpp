// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Game.hpp"

#include <algorithm>
#include <iomanip>
#include <sstream>

///////////////////////////////////////////////////////////////////////////////
// Game
///////////////////////////////////////////////////////////////////////////////

Game::Game():
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
    btScalar x = _prng.generate(-4, 4);
    btScalar z = _prng.generate(-4, 4);
//    x=3.10056;
//    z=0.80692;
    _jack = {btTransform(btQuaternion(0,0,0,1),btVector3(x,0.2,z)),
        btVector3(0, 0, 0), 0.1, 0.2};

    _redBalls.clear();
    _blueBalls.clear();
}

//renvoi meilleur distance de chaque joueur
std::vector<double> Game::bestDistancePlayer(GameResult result) const{
     
    std::vector<double> vec (2,1000.0);
    
    //toutes les boules
    for (BallResult & b :  result._ballResults) {  
        if( vec[b._player] > b._distanceToJack ){
            vec[b._player] = b._distanceToJack; 
        }    
    }
    
  return vec;
    
    
}

int Game::fitness(const Game & game,GameResult result) const
{
   

  return 0;
}

bool Game::isGameFinished() const
{
    const btVector3 & jackPosition = getJack().getPosition();
    return (_remainingBallsBlue == 0 and _remainingBallsRed == 0)
        or not isValidPosition(jackPosition);
}

bool Game::isValidPosition(const btVector3 & position) const
{
    return position.length2() < 100;
}

GameResult Game::computeResult() const
{
    if (_redBalls.empty() and _blueBalls.empty())
        return {PLAYER_NONE, 0, {}};

    GameResult res;

    // get jack
    const GameBall & jack = getJack();
    btVector3 jackPos = jack.getPosition();

    // compute ball results (distance from jack)
    auto distanceFun = [&jackPos] (const GameBall & b, player_t p)
    {
        btVector3 bPos = b.getPosition();
        btVector3 v = bPos - jackPos;
        return BallResult{p, v.length(), bPos, false};
    };
    std::transform(_redBalls.begin(), _redBalls.end(),
            std::back_inserter(res._ballResults),
            std::bind(distanceFun, std::placeholders::_1, PLAYER_RED));
    std::transform(_blueBalls.begin(), _blueBalls.end(),
            std::back_inserter(res._ballResults),
            std::bind(distanceFun, std::placeholders::_1, PLAYER_BLUE));
    assert(not res._ballResults.empty());

    if (isValidPosition(jackPos))
    {
        // sort balls by distance from jack
        auto cmpFun = [] (const BallResult & b1, const BallResult & b2)
        { return b1._distanceToJack < b2._distanceToJack; };
        std::sort(res._ballResults.begin(), res._ballResults.end(), cmpFun);
        // find winning balls
        res._winningPlayer = res._ballResults.front()._player;
        res._nbWinningBalls = 0;
        for (BallResult & b : res._ballResults)
        {
            if (b._player==res._winningPlayer and isValidPosition(b._position))
            {
                b._isWinning = true;
                res._nbWinningBalls++;
            }
            else break;
        }
    }
    else
    {
        res._nbWinningBalls = 0;
        res._winningPlayer = PLAYER_NONE;
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
    //Le vecteur doit rester dans son ordre naturel: le dernier lancé en derniere position.
    return _redBalls;
}

const std::vector<GameBall> & Game::getBlueBalls() const
{
    //Le vecteur doit rester dans son ordre naturel: le dernier lancé en derniere position.
    return _blueBalls;
}

const std::vector<GameBall> & Game::getPlayerBalls(player_t player) const
{
    if(player == PLAYER_RED){
        return getRedBalls();
    }else if(player == PLAYER_BLUE){
        return getBlueBalls();
    }else{
        std::vector<GameBall> none;
        return none;
    }
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

VecParam Game::getMinParams() const
{
    return VecParam {-90, -180, 0};
}

VecParam Game::getMaxParams() const
{
    return VecParam {90, 180, 10};
}

void Game::throwBall(const VecParam & params)
{
    // create ball
    createBall(params);

    Physics physics;
    physics.addBall(&_jack);
    for (GameBall & b : _redBalls)
        physics.addBall(std::addressof(b));
    for (GameBall & b : _blueBalls)
        physics.addBall(std::addressof(b));
    //physics.computeSimulation(0.1);
    physics.computeSimulation(10);

    // TODO ground limits for physics

    updateCurrentPlayer();
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

void Game::createBall(const VecParam & p)
{
    if (_currentPlayer == PLAYER_NONE)
        return;

    // get velocity vector from the interface
    VecParam pmin = getMinParams();
    VecParam pmax = getMaxParams();
    VecParam clampedP = p.cwiseMin(pmax).cwiseMax(pmin);
    double radPitch = degToRad(clampedP(0));
    double radYaw = degToRad(clampedP(1));
    double velocity = clampedP(2);

    // compute velocity vector from pitch/yaw
    double vx = velocity * cos(radPitch) * cos(radYaw);
    double vy = velocity * sin(radPitch);
    double vz = velocity * cos(radPitch) * sin(radYaw);

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

///////////////////////////////////////////////////////////////////////////////
// GameInteractive
///////////////////////////////////////////////////////////////////////////////

void GameInteractive::interactiveThrowStart(const VecParam & params)
{
    // create ball
    createBall(params);

    // create physics
    _uptrPhysics.reset(new Physics);
    _uptrPhysics->addBall(&_jack);
    for (GameBall & b : _redBalls)
        _uptrPhysics->addBall(std::addressof(b));
    for (GameBall & b : _blueBalls)
        _uptrPhysics->addBall(std::addressof(b));
}

bool GameInteractive::interactiveThrowRunning()
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

void GameInteractive::interactiveThrowContinue(double duration)
{
    _uptrPhysics->computeSimulation(duration);
}
