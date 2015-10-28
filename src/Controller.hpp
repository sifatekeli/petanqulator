
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

        const Ground & getGround() const;
        const std::vector<Ball> & getBalls() const;

        void newGame();
        void startThrow(double vx, double vy, double vz);
        void updateThrow(double duration);

        vec3 getShooterPosition() const;
        const Ball & getJack() const;

        bool isGameFinished() const;
        player_t getCurrentPlayer() const;
        void getBestPlayerStats(player_t & player, 
                int & nbBalls) const;
};

#endif

