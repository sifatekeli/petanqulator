
#include "Controller.hpp"

Controller::Controller(int argc, char ** argv):
    _view(*this, argc, argv)
{}

void Controller::run()
{
    _view.run();
}

const Ground & Controller::getGround() const
{
    return _game.getGround();
}

const std::vector<Ball> & Controller::getBalls() const
{
    return _game.getBalls();
}

void Controller::newGame()
{
    _game.newGame();
    _view.stopAnimation();
    _view.update();
}

void Controller::startThrow()
{
    _game.interactiveThrowStart();
    _view.startAnimation();
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

void Controller::getBestPlayerStats(player_t & player, 
        int & nbBalls) const
{
    _game.getBestPlayerStats(player, nbBalls);
}


