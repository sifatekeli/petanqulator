// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include <petanqulator/Player.hpp>

void displayBall(const std::string & name, const GameBall & ball)
{
    btVector3 position = ball._transform.getOrigin();
    std::cout << name << " " << position << std::endl;
}

void displayBalls(const std::string & name, const std::vector<GameBall> & balls)
{
    for (const GameBall & b : balls)
        displayBall(name, b);
}

int main()
{
    PlayerBestRandom player;
    player._params["nbTries"] = 10;

    // create game
    Game game;
    game.newGame();

    // initial game
    displayBall("jack", game.getJack());
    displayBalls("red", game.getRedBalls());
    displayBalls("blue", game.getBlueBalls());
    std::cout << std::endl;

    // throw a ball
    ThrowParams params = player.chooseParams(game);
    game.throwBall(params);
    displayBall("jack", game.getJack());
    displayBalls("red", game.getRedBalls());
    displayBalls("blue", game.getBlueBalls());

    return 0;
}

