
#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

#include "Game.hpp"
#include "View.hpp"

class Controller
{
    private:
        Game _game;
        View _view;

    public:
        Controller(int argc, char ** argv);
        void run();

        const Game::Ball & getJack() const;
        const Game::Ground & getGround() const;
        const std::vector<Game::Ball> & getRedBalls() const;
        const std::vector<Game::Ball> & getBlueBalls() const;

        vec3 getShooterPosition() const;
        int getRemainingBallsRed() const;
        int getRemainingBallsBlue() const;

        void newGame();
        void startThrow(double vx, double vy, double vz);
        void updateThrow(double duration);

        bool isGameFinished() const;
        Game::player_t getCurrentPlayer() const;
        void getBestPlayerStats(Game::player_t & player, 
                int & nbBalls) const;
};

#endif

