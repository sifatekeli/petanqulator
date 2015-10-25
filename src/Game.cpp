
#include "Game.hpp"

Game::Game()
{
    newGame();
}

void Game::newGame()
{
    _nbRemainingRedBalls = 3;
    _redBalls.clear();
    _nbRemainingBlueBalls = 3;
    _blueBalls.clear();
    _currentPlayer = "red";
    _status = "current player: red";
}

const std::string & Game::getStatus() const
{
    return _status;
}

