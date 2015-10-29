
#include "Controller.hpp"

Controller::Controller(int argc, char ** argv):
    _view(*this, argc, argv)
{}

void Controller::run()
{
    _view.run();
}

const Game::Ball & Controller::getJack() const
{
    return _game.getJack();
}

const Game::Ground & Controller::getGround() const
{
    return _game.getGround();
}

const std::vector<Game::Ball> & Controller::getRedBalls() const
{
    return _game.getRedBalls();
}

const std::vector<Game::Ball> & Controller::getBlueBalls() const
{
    return _game.getBlueBalls();
}

void Controller::newGame()
{
    _game.newGame();

    vec3 jackPos = getJack()._position;
    std::stringstream ss;
    ss << "new game, jack=[" << jackPos.getX() << ' ' << jackPos.getY() << ' '
        << jackPos.getZ() << ']';
    UTILS_INFO(ss.str());

    _view.stopAnimation();
    _view.update();
}

void Controller::startThrow(double vx, double vy, double vz)
{
    // output log
    std::stringstream ss;
    ss << "throw ball, velocity=[" << vx << ' ' << vy << ' ' << vz << ']';
    UTILS_INFO(ss.str());

    // TODO interactive simulation
    _game.throwBall(vx, vy, vz);
    _view.update();
    /*
    if (not _game.isGameFinished())
    {
        _game.interactiveThrowStart(vx, vy, vz);
        _view.startAnimation();
    }
    */
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

Game::player_t Controller::getCurrentPlayer() const
{
    return _game.getCurrentPlayer();
}

void Controller::getBestPlayerStats(Game::player_t & player, 
        int & nbBalls) const
{
    _game.getBestPlayerStats(player, nbBalls);
}

vec3 Controller::getShooterPosition() const
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

