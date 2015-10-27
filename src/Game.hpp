
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Physics.hpp"

#include <string>

class Game
{
    private:
        Physics _physics;
        float _timeStep;
        int _remainingBallsRed;
        int _remainingBallsBlue;
        player_t _currentPlayer;
        player_t _opponentPlayer;

    public:
        Game();

        void newGame();
        bool isGameFinished() const;
        player_t getCurrentPlayer() const;
        void getBestPlayerStats(player_t & player, int & nbBalls) const;

        // throw one ball and compute physics simulation till stationnarity
        void throwBall();

        // step-by-step simulation (for interactive display)
        void interactiveThrowStart();
        bool interactiveThrowRunning() const;
        void interactiveThrowContinue(float duration);

        const Ground & getGround() const;
        const std::vector<Ball> & getBalls() const;
};

#endif

