
#include "Game.hpp"

#include <algorithm>
#include <sstream>

Game::Game()
{}

void Game::newGame()
{
    // players and teams
    _remainingBallsRed = 2;
    _remainingBallsBlue = 2;
    _currentPlayer = PLAYER_RED;
    _shooterPosition = vec3(0, -8, 1);

    // ground
    _ground = {-6, 6, -10, 10};

    // jack
    // TODO init jack at a random position
    _jack = {vec3(0, 4, 4), 0.1, 0.1};

    _redBalls.clear();
    _blueBalls.clear();

}

bool Game::isGameFinished() const
{
    return _remainingBallsBlue == 0 and _remainingBallsRed == 0;
}

void Game::getBestPlayerStats(player_t & player, int & nbBalls) const
{
    // TODO
    /*
    // get jack
    const Ball & jack = getJack();

    // sort balls according to their distance to the jack
    std::vector<Ball> balls(_physics._balls.size()-1);
    auto cmpBalls = [&jack] (const Ball & b1, const Ball & b2)
    {
        vec3 d1 = b1._position - jack._position;
        vec3 d2 = b2._position - jack._position;
        return d1.length2() < d2.length2();
    };
    std::partial_sort_copy(_physics._balls.begin()+1, _physics._balls.end(),
            balls.begin(), balls.end(), cmpBalls);

    // get the first balls from the same player
    player = (player_t) balls.front()._player;
    nbBalls = 0;
    for (const Ball & b : balls)
        if (b._player == player)
            nbBalls++;
        else
            break;
            */
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

vec3 Game::getShooterPosition() const
{
    return _shooterPosition;
}

void Game::throwBall(double vx, double vy, double vz)
{
    // create ball
    //createBall(vx, vy, vz);

    _uptrPhysics.reset(new Physics(&_jack));
    {
    _uptrPhysics->computeSimulation(0.1);
    std::stringstream ss;
    ss << "position=[" << _jack._position.getX() << ' ' 
        << _jack._position.getY() << ' ' << _jack._position.getZ() << ']';
    UTILS_INFO(ss.str());
    }

    // TODO _uptrPhysics = std::make_unique<Physics>();
    // run simulation
    /*
    _physics.startSimulation();
    while (_physics.isSimulationRunning())
        // TODO tune that
        _physics.computeSimulation(0.2);
    // TODO ground limits for physics
    */

    updatePlayer();
}

void Game::interactiveThrowStart(double vx, double vy, double vz)
{
    // create ball
    createBall(vx, vy, vz);

    // start simulation
    // TODO _physics.startSimulation();
    _uptrPhysics.reset(new Physics(&_jack));
}

bool Game::interactiveThrowRunning() 
{
    // TODO ground limits for physics
    if (_uptrPhysics->isSimulationRunning())
    {
        return true;
    }
    else
    {
        _uptrPhysics.reset();
        updatePlayer();
        return false;
    }
}

void Game::interactiveThrowContinue(double duration)
{

    _uptrPhysics->computeSimulation(duration);

    /*
    std::stringstream ss;
    ss << "position=[" << _jack._position.getX() << ' ' 
        << _jack._position.getY() << ' ' << _jack._position.getZ() << ']';
    UTILS_INFO(ss.str());
    */

    // TODO
    /*
    double t = duration;
    while (t - _timeStep > 0 and interactiveThrowRunning())
    {
        _physics.computeSimulation(_timeStep);
        t -= _timeStep;
    }
    if (t > 1e-4 and interactiveThrowRunning())
        _physics.computeSimulation(t);
        */
}

void Game::createBall(double vx, double vy, double vz)
{
    // update game data
    if (_currentPlayer == PLAYER_BLUE)
    {
        // TODO add ball in Physics
        _blueBalls.push_back({_shooterPosition, 0.2, 0.2});
        _remainingBallsBlue--;
    }
    else if (_currentPlayer == PLAYER_RED)
    {
        _redBalls.push_back({_shooterPosition, 0.2, 0.2});
        _remainingBallsRed--;
    }
}

void Game::updatePlayer()
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

