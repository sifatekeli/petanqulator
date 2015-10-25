
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Physics.hpp"

#include <string>

class Game
{
    private:
        Physics _physics;
        Ball * _ptrJack;
        std::vector<Ball*> _redBalls;
        std::vector<Ball*> _blueBalls;
        int _nbRemainingRedBalls;
        int _nbRemainingBlueBalls;
        std::string _currentPlayer;
        std::string _status;

    public:
        Game();
        void newGame();
        const std::string & getStatus() const;
};

#endif

