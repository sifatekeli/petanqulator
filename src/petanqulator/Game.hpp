// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "GameObject.hpp"
#include "Physics.hpp"
#include "Prng.hpp"

#include <memory>
#include <string>
#include <vector>

enum player_t { PLAYER_RED, PLAYER_BLUE, PLAYER_NONE };

struct BallResult
{
    player_t _player;
    btScalar _distanceToJack;
    btVector3 _position;
    bool _isWinning;
};

struct GameResult
{
    player_t _winningPlayer;
    int _nbWinningBalls;
    std::vector<BallResult> _ballResults;
};

//lancer
struct ThrowParams
{
    double _pitch;
    double _yaw;
    double _velocity;
};

std::ostream & operator<<(std::ostream & os, const ThrowParams & p);

class Game
{
    protected:
        Prng _prng;
        player_t _currentPlayer;
        int _remainingBallsRed;
        int _remainingBallsBlue;
        std::vector<GameBall> _redBalls;
        std::vector<GameBall> _blueBalls;
        GameBall _jack;
        GameGround _ground;
        btVector3 _shooterPosition;

        // TODO detect invalid jack -> draw

    public:
        Game();

        void newGame();
        int fitness(const GameResult & result) const;
        bool isGameFinished() const;
        GameResult computeResult() const;
        player_t getCurrentPlayer() const;
        bool isValidPosition(const btVector3 & position) const;

        int getRemainingBallsRed() const;
        int getRemainingBallsBlue() const;
        const std::vector<GameBall> & getRedBalls() const;
        const std::vector<GameBall> & getBlueBalls() const;
        const std::vector<GameBall> & getPlayerBalls(player_t player) const;
        const GameGround & getGround() const;
        const GameBall & getJack() const;
        btVector3 getShooterPosition() const;

        ThrowParams getMinParams() const;
        ThrowParams getMaxParams() const;

        // throw one ball and compute physics simulation till stationnarity
        void throwBall(const ThrowParams & params);

    protected:
        void createBall(const ThrowParams & params);
        void updateCurrentPlayer();
};

class GameInteractive : public Game
{
    private:
        std::unique_ptr<Physics> _uptrPhysics;

    public:
        // step-by-step simulation (for interactive display)
        void interactiveThrowStart(const ThrowParams & params);
        bool interactiveThrowRunning();
        void interactiveThrowContinue(double duration);
};

#endif
