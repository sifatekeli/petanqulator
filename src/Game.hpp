
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Physics.hpp"

#include <string>

class Game
{
    private:
        Physics _physics;
        std::vector<int> _remainingBalls;
        std::vector<int> _teamOfPlayers;
        int _currentPlayer;

    public:
        Game();

        void newGame();
        bool isGameFinished() const;
        int getCurrentPlayer() const;
        void getBestPlayerStats(int & team, int & nbBalls) const;

        // throw one ball and compute physics simulation till stationnarity
        void throwBall();

        // step-by-step simulation (for interactive display)
        void interactiveThrowStart();
        bool interactiveThrowFinished() const;
        void interactiveThrowContinue();

        const Ground & getGround() const;
        const std::vector<Ball> & getBalls() const;
        const std::vector<int> & getTeamOfPlayers() const;
};

#endif

