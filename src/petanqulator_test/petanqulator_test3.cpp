// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include <petanqulator/Player.hpp>

#include <iomanip>

using namespace std;

void displayPosition(const GameBall & ball)
{
    std::cout << ball._transform.getOrigin();
}

int main()
{

    Game game0;
    game0.newGame();

    cout << "pitch yaw velocity xball yball zball distance xjack yjack zjack \n";

    for (double yaw=-70.0; yaw<71.0; yaw+=1.0) {

        // run game
        Game game(game0);
        VecParam params {32.0, yaw, 3.0};
        game.throwBall(params);
        GameResult result = game.computeResult();

        // output results
        // params
        cout << params[0] << ' ' << params[1] << ' ' << params[2] << ' ';
        // ball
        const auto & ball = result._ballResults.back()._position;
        cout << ball[0] << ' ' << ball[1] << ' ' << ball[2] << ' ';
        // distance
        const auto & distance = result._ballResults.back()._distanceToJack;
        cout << distance << ' ';
        // jack
        const auto & jack = game.getJack()._transform.getOrigin();
        cout << jack[0] << ' ' << jack[1] << ' ' << jack[2] << ' ';
        cout << endl;

        /*
        // output balls
        for (unsigned i=0; i<result._ballResults.size(); ++i) {
           const auto & b = result._ballResults[i];
           std::cout << "BALL " << i << " ";
           switch (b._player) {
               case PLAYER_RED: std::cout << "red "; break;
               case PLAYER_BLUE: std::cout << "blue "; break;
               case PLAYER_NONE: std::cout << "none "; break;
               default: std::cout << "unknown "; break;
           }
           std::cout << b._distanceToJack << " "
               << b._position << " "
               << b._isWinning << std::endl;
        }
        std::cout << std::endl;
    */

    }

    return 0;
}
