// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include <petanqulator/Player.hpp>

#include <cassert>

using namespace std;

int main() {

    Game game0;
    game0.newGame();

    cout << "pitch yaw velocity xball yball zball distance xjack yjack zjack \n";

    for (double pitch=-90.0; pitch<90.0; pitch+=1.0) {
        for (double yaw=-70.0; yaw<70.0; yaw+=1.0) {
            for (double velocity=1.0; velocity<8.0; velocity+=1.0) {

                // run game
                Game game(game0);
                VecParam params {pitch, yaw, velocity};
                game.throwBall(params);
                GameResult result = game.computeResult();
                assert(result._ballResults.size() == 1);

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
            }
        }
    }

    return 0;
}


