// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include <petanqulator/Game.hpp>

void displayBall(const std::string & name, const GameBall & ball)
{
    btVector3 position = ball._transform.getOrigin();
    std::cout << name << ": " << position.getX() << ' ' << position.getY()
        << ' ' << position.getZ() << ']' << std::endl;
}

void displayBalls(const std::string & name, const std::vector<GameBall> & balls)
{
    for (const GameBall & b : balls)
        displayBall(name, b);
}

int main()
{
    // create game
    Game game;
    game.newGame();

    // initial game
    displayBall("jack", game.getJack());
    displayBalls("red", game.getRedBalls());
    displayBalls("blue", game.getBlueBalls());

    // throw a ball
    game.throwBall(1, 1, 0);
    displayBall("jack", game.getJack());
    displayBalls("red", game.getRedBalls());
    displayBalls("blue", game.getBlueBalls());

    // throw a ball
    game.throwBall(1, 1, 1);
    displayBall("jack", game.getJack());
    displayBalls("red", game.getRedBalls());
    displayBalls("blue", game.getBlueBalls());

    return 0;
}

