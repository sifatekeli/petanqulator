// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include <petanqulator/Game.hpp>

#include "View.hpp"

class Controller
{
    private:
        GameInteractive _game;
        View _view;

    public:
        Controller(int argc, char ** argv);
        void run();

        const GameBall & getJack() const;
        const GameGround & getGround() const;
        const std::vector<GameBall> & getRedBalls() const;
        const std::vector<GameBall> & getBlueBalls() const;
        const GameInteractive & getGame() const;
        btVector3 getShooterPosition() const;
        int getRemainingBallsRed() const;
        int getRemainingBallsBlue() const;

        VecParam getMinParams() const;
        VecParam getMaxParams() const;

        void newGame();
        void startThrow(const VecParam & params);
        void updateThrow(double duration);

        bool isGameFinished() const;
        player_t getCurrentPlayer() const;
        GameResult computeGameResult() const;
};

#endif

