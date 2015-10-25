
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <string>
#include <vector>

struct Ball
{
};

struct Ground
{
};

class Game
{
    private:
        Ball _jack;

        int _nbRemainingRedBalls;
        std::vector<Ball> _redBalls;

        int _nbRemainingBlueBalls;
        std::vector<Ball> _blueBalls;

        std::string _currentPlayer;

        std::string _status;

    public:
        Game();
        void newGame();
        const std::string & getStatus() const;
};

#endif

