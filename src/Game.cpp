
#include "Game.hpp"

#include <algorithm>

Game::Game()
{}

void Game::newGame()
{
    // players and teams
    _remainingBallsRed = 2;
    _remainingBallsBlue = 2;
    _currentPlayer = PLAYER_RED;
    _shooterPosition = vec3(-8,1,0);

    // physics
    _physics._motionThreshold = 1e-9;
    _timeStep = 1e-3;

    // forces
    _physics._uptrForces.clear();
    _physics._uptrForces.emplace_back(new Gravity(0, -9.8f, 0));
    _physics._uptrForces.emplace_back(new Viscosity(200));

    // ground
    _physics._ground = Ground(PLAYER_NONE, INFINITY, vec3(0,0,0), 
            vec3(0,0,0), -10, 10, -6, 6, 0.5);

    // jack
    _physics._balls.clear();
    // TODO init jack at a random position
    _physics._balls.emplace_back(
            PLAYER_JACK, 1, vec3(0,5,0), vec3(0,0,0), 0.1);

    // TODO ground limits for physics
}

bool Game::isGameFinished() const
{
    return _remainingBallsBlue == 0 and _remainingBallsRed == 0;
}

player_t Game::getCurrentPlayer() const
{
    return _currentPlayer;
}

void Game::getBestPlayerStats(player_t & player, int & nbBalls) const
{
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
    player = balls.front()._player;
    nbBalls = 0;
    for (const Ball & b : balls)
        if (b._player == player)
            nbBalls++;
        else
            break;
}

void Game::throwBall(double vx, double vy, double vz)
{
    // create ball
    createBall(vx, vy, vz);

    // run simulation
    _physics.startSimulation();
    while (_physics.isSimulationRunning())
        _physics.computeSimulation(_timeStep);

    updatePlayer();
}

void Game::interactiveThrowStart(double vx, double vy, double vz)
{
    // create ball
    createBall(vx, vy, vz);

    // start simulation
    _physics.startSimulation();
}

bool Game::interactiveThrowRunning() 
{
    if (_physics.isSimulationRunning())
    {
        return true;
    }
    else
    {
        updatePlayer();
        return false;
    }
}

void Game::interactiveThrowContinue(double duration)
{
    double t = duration;
    while (t - _timeStep > 0 and interactiveThrowRunning())
    {
        _physics.computeSimulation(_timeStep);
        t -= _timeStep;
    }
    if (t > 1e-4 and interactiveThrowRunning())
        _physics.computeSimulation(t);
}

const Ground & Game::getGround() const
{
    return _physics._ground;
}

const std::vector<Ball> & Game::getBalls() const
{
    return _physics._balls;
}

vec3 Game::getShooterPosition() const
{
    return _shooterPosition;
}

const Ball & Game::getJack() const
{
    const Ball & jack = _physics._balls.front();
    if (jack._player != PLAYER_JACK)
        UTILS_ERROR("invalid jack");
    return jack;
}

int Game::getRemainingBallsRed() const
{
    return _remainingBallsRed;
}

int Game::getRemainingBallsBlue() const
{
    return _remainingBallsBlue;
}

void Game::createBall(double vx, double vy, double vz)
{
    // update game data
    if (_currentPlayer == PLAYER_NONE)
        return;
    else if (_currentPlayer == PLAYER_RED)
        _remainingBallsRed--;
    else
        _remainingBallsBlue--;

    // create ball
    _physics._balls.emplace_back(
            _currentPlayer, 5, _shooterPosition, vec3(vx,vy,vz), 0.1);
}

void Game::updatePlayer()
{
    // first throw (jack + red ball), switch to blue
    if (_physics._balls.size() <= 2)
        _currentPlayer = PLAYER_BLUE;
    // one or more player cannot play
    else if (_remainingBallsRed == 0 and _remainingBallsBlue > 0)
        _currentPlayer = PLAYER_BLUE;
    else if (_remainingBallsBlue == 0 and _remainingBallsRed > 0)
        _currentPlayer = PLAYER_RED;
    else if (_remainingBallsBlue == 0 and _remainingBallsRed == 0)
        _currentPlayer = PLAYER_NONE;
    // all player can play, switch to looser
    else
    {
        player_t bestPlayer;
        int nbBalls;
        getBestPlayerStats(bestPlayer, nbBalls);
        _currentPlayer = bestPlayer == PLAYER_RED ? PLAYER_BLUE : PLAYER_RED;
    }
}

