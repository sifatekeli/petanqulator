
#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "GameObject.hpp"
#include "Physics.hpp"
#include "Utils.hpp"

#include <memory>
#include <string>
#include <vector>

enum player_t {PLAYER_RED, PLAYER_BLUE, PLAYER_NONE};

class Game
{
    private:
        player_t _currentPlayer;
        int _remainingBallsRed;
        int _remainingBallsBlue;
        std::vector<GameBall> _redBalls;
        std::vector<GameBall> _blueBalls;
        GameBall _jack;
        GameGround _ground;
        vec3 _shooterPosition;
        std::unique_ptr<Physics> _uptrPhysics;

    public:
        Game();

        void newGame();
        bool isGameFinished() const;
        void getBestPlayerStats(player_t & player, int & nbBalls) const;
        player_t getCurrentPlayer() const;

        int getRemainingBallsRed() const;
        int getRemainingBallsBlue() const;
        const std::vector<GameBall> & getRedBalls() const;
        const std::vector<GameBall> & getBlueBalls() const;
        const GameGround & getGround() const;
        const GameBall & getJack() const;
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

