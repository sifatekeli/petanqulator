
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "Physics.hpp"
#include "Utils.hpp"

#include <string>

class Game
{
    public:
        enum player_t {PLAYER_RED, PLAYER_BLUE, PLAYER_NONE};

        struct Ball
        {
            vec3 _position;
            vec3 _velocity;
            real _mass;
            real _radius;
        };

        struct Ground
        {
            real _xMin, _xMax, _yMin, _yMax;
        };

    private:
        Physics _physics;
        player_t _currentPlayer;
        int _remainingBallsRed;
        int _remainingBallsBlue;
        std::vector<Ball> _redBalls;
        std::vector<Ball> _blueBalls;
        Ball _jack;
        Ground _ground;
        vec3 _shooterPosition;

    public:
        Game();

        void newGame();
        bool isGameFinished() const;
        void getBestPlayerStats(player_t & player, int & nbBalls) const;
        player_t getCurrentPlayer() const;

        int getRemainingBallsRed() const;
        int getRemainingBallsBlue() const;
        const std::vector<Ball> & getRedBalls() const;
        const std::vector<Ball> & getBlueBalls() const;
        const Ground & getGround() const;
        const Ball & getJack() const;
        vec3 getShooterPosition() const;

        // throw one ball and compute physics simulation till stationnarity
        void throwBall(double vx, double vy, double vz);

        // step-by-step simulation (for interactive display)
        void interactiveThrowStart(double vx, double vy, double vz);
        bool interactiveThrowRunning();
        void interactiveThrowContinue(double duration);

    private:
        void createBall(double vx, double vy, double vz);
        void updatePlayer();
};

#endif

