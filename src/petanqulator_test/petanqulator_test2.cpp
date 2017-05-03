// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include <petanqulator/Player.hpp>

#include <cassert>

using namespace std;

int main()
{
    Game game0;
    game0.newGame();

    for (double yaw=-90.0; yaw<90.0; yaw+=0.5)
    {
        Game game(game0);
        VecParam params = {45, yaw, 1};
        game.throwBall(params);
        GameResult result = game.computeResult();
        assert(result._ballResults.size() == 1);

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

    /*

    displayPosition(game.getJack());
    GameResult result = game.computeResult();
    for (const auto & r : result._ballResults)
        cout << r._position << ' ' << setprecision(2) << float(r._distanceToJack) << endl;
    */

    return 0;
}


