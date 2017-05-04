// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include <petanqulator/Player.hpp>

#include <cassert>
#include <fstream>

using namespace std;

int main(int argc, char ** argv) {

    if (argc != 2) {
        cerr << "usage: " << argv[0] << " outfile\n";
        exit(-1);
    }

    fstream file(argv[1]);
    Game game0;
    game0.newGame();

    file << "pitch yaw velocity xball yball zball distance xjack yjack zjack \n";

    for (double pitch=-10.0; pitch<81.0; pitch+=1.0) {
        for (double yaw=-70.0; yaw<71.0; yaw+=1.0) {
            for (double velocity=1.0; velocity<8.0; velocity+=0.5) {

                // run game
                Game game(game0);
                VecParam params {pitch, yaw, velocity};
                game.throwBall(params);
                GameResult result = game.computeResult();
                assert(result._ballResults.size() == 1);

                // output results
                // params
                file << params[0] << ' ' << params[1] << ' ' << params[2] << ' ';
                // ball
                const auto & ball = result._ballResults.back()._position;
                file << ball[0] << ' ' << ball[1] << ' ' << ball[2] << ' ';
                // distance
                const auto & distance = result._ballResults.back()._distanceToJack;
                file << distance << ' ';
                // jack
                const auto & jack = game.getJack()._transform.getOrigin();
                file << jack[0] << ' ' << jack[1] << ' ' << jack[2] << ' ';
                file << endl;
            }
        }
    }

    return 0;
}


