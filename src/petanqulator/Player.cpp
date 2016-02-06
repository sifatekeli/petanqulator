// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Player.hpp"

#include <iostream>
#include <iomanip>

ThrowParams PlayerRandom::chooseParams(const Game & game) 
{
    ThrowParams pmin = game.getMinParams();
    ThrowParams pmax = game.getMaxParams();
    double pitch = _prng.generate(pmin._pitch, pmax._pitch);
    double yaw = _prng.generate(pmin._yaw, pmax._yaw);
    double velocity = _prng.generate(pmin._velocity, pmax._velocity);
    /*
    double pitch = _prng.generate(0, 70);
    double yaw = _prng.generate(-90, 90);
    double velocity = _prng.generate(1, 7);
    */
    return ThrowParams {pitch, yaw, velocity};
}

PlayerBestRandom::PlayerBestRandom()
{
    _params["nbTries"] = 10;
}

ThrowParams PlayerBestRandom::chooseParams(const Game & game) 
{
    int nbTries = _params["nbTries"];
    ThrowParams bestParams = PlayerRandom::chooseParams(game);
    player_t currentPlayer = game.getCurrentPlayer();
    for (int i=1; i<nbTries; i++)
    {
        ThrowParams testParams = PlayerRandom::chooseParams(game);
        Game testGame(game);
        testGame.throwBall(testParams);
        GameResult result = testGame.computeResult();
        if (result._winningPlayer == currentPlayer)
            bestParams = testParams;
        // TODO test other reward policy (nb winning balls, min distance...)

#ifdef LOG
        std::cout << testParams; 
        if (result._winningPlayer == currentPlayer)
        {
        const BallResult & br = result._ballResults.front();
            std::cout << " better"
                << " " << br._position
                << " " << std::setprecision(4) << br._distanceToJack;
        }
        std::cout << std::endl;
#endif

    }

    return bestParams;
}


