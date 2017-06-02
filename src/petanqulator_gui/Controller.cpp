// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Controller.hpp"

#include <vector>

Controller::Controller(int argc, char ** argv):
    _view(*this, argc, argv)
{}

void Controller::run()
{
    _view.run();
}

const GameBall & Controller::getJack() const
{
    return _game.getJack();
}

const GameGround & Controller::getGround() const
{
    return _game.getGround();
}

const std::vector<GameBall> & Controller::getRedBalls() const
{
    return _game.getRedBalls();
}

const std::vector<GameBall> & Controller::getBlueBalls() const
{
    return _game.getBlueBalls();
}

const GameInteractive & Controller::getGame() const
{
    return _game;
}


void Controller::newGame()
{
    _game.newGame();

    btVector3 jackPos = getJack()._transform.getOrigin();
    std::stringstream ss;
    ss << "new game, jack=[" << jackPos.getX() << ' ' << jackPos.getY() << ' '
        << jackPos.getZ() << ']';
    UTILS_INFO(ss.str());

    _view.stopAnimation();
    _view.update();
}

void Controller::startThrow(const VecParam & params)
{
    // log
    std::stringstream ss;
    ss << "throw ball, player=" 
        << (_game.getCurrentPlayer() == PLAYER_RED ? "red" : "blue")
        << ", pitch=" << params(0) 
        << ", yaw=" << params(1)
        << ", velocity=" << params(2) << std::endl;
    UTILS_INFO(ss.str());

    if (not _game.isGameFinished())
    {
        _game.interactiveThrowStart(params);
        _view.startAnimation();
    }
}

void Controller::updateThrow(double duration)
{
    if (_game.interactiveThrowRunning())
        _game.interactiveThrowContinue(duration);
    else
        _view.stopAnimation();
}

bool Controller::isGameFinished() const
{
    return _game.isGameFinished();
}

player_t Controller::getCurrentPlayer() const
{
    return _game.getCurrentPlayer();
}

GameResult Controller::computeGameResult() const
{
    return _game.computeResult();
}

btVector3 Controller::getShooterPosition() const
{
    return _game.getShooterPosition();
}

int Controller::getRemainingBallsRed() const
{
    return _game.getRemainingBallsRed();
}

int Controller::getRemainingBallsBlue() const
{
    return _game.getRemainingBallsBlue();
}

VecParam Controller::getMinParams() const
{
    return _game.getMinParams();
}

VecParam Controller::getMaxParams() const
{
    return _game.getMaxParams();
}


