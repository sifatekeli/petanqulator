
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
    _view.update();
}

void Controller::throwBall()
{
    _game.throwBall();
    _view.update();
}

