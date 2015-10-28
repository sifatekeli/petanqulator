
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Physics.hpp"

#include <string>

class Game
{
    private:
        Physics _physics;
        double _timeStep;
        int _remainingBallsRed;
        int _remainingBallsBlue;
        player_t _currentPlayer;
        player_t _opponentPlayer;
        vec3 _shooterPosition;

    public:
        Game();

        void newGame();
        bool isGameFinished() const;
        player_t getCurrentPlayer() const;
        void getBestPlayerStats(player_t & player, int & nbBalls) const;

        // throw one ball and compute physics simulation till stationnarity
        void throwBall(double vx, double vy, double vz);

        // step-by-step simulation (for interactive display)
        void interactiveThrowStart(double vx, double vy, double vz);
        bool interactiveThrowRunning() const;
        void interactiveThrowContinue(double duration);

        const Ground & getGround() const;
        const std::vector<Ball> & getBalls() const;

        vec3 getShooterPosition() const;
        const Ball & getJack() const;

    private:
        void createBall(double vx, double vy, double vz);
};

#endif

