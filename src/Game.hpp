// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "GameObject.hpp"
#include "Physics.hpp"

#include <memory>
#include <random>
#include <string>
#include <vector>

enum player_t {PLAYER_RED, PLAYER_BLUE, PLAYER_NONE};

struct BallResult
{
    player_t _player;
    btScalar _distance;
    bool _isWinning;
};

struct GameResult 
{
    player_t _winningPlayer;
    int _nbWinningBalls;
    std::vector<BallResult> _ballResults;
};

class Game
{
    private:
        std::mt19937 _engine;
        std::uniform_real_distribution<btScalar> _distribution;
        player_t _currentPlayer;
        int _remainingBallsRed;
        int _remainingBallsBlue;
        std::vector<GameBall> _redBalls;
        std::vector<GameBall> _blueBalls;
        GameBall _jack;
        GameGround _ground;
        btVector3 _shooterPosition;
        std::unique_ptr<Physics> _uptrPhysics;

        // TODO detect invalid jack -> draw
        // TODO check memory usage 

    public:
        Game();

        void newGame();
        bool isGameFinished() const;
        GameResult computeResult() const;
        player_t getCurrentPlayer() const;

        int getRemainingBallsRed() const;
        int getRemainingBallsBlue() const;
        const std::vector<GameBall> & getRedBalls() const;
        const std::vector<GameBall> & getBlueBalls() const;
        const GameGround & getGround() const;
        const GameBall & getJack() const;
        btVector3 getShooterPosition() const;

        // throw one ball and compute physics simulation till stationnarity
        void throwBall(double vx, double vy, double vz);

        // step-by-step simulation (for interactive display)
        void interactiveThrowStart(double vx, double vy, double vz);
        bool interactiveThrowRunning();
        void interactiveThrowContinue(double duration);

    private:
        void createBall(double vx, double vy, double vz);
        void updateCurrentPlayer();
};

#endif

