// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include <petanqulator/Player.hpp>

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
    PlayerRandom redPlayer;
    PlayerBestRandom bluePlayer;

    std::vector<std::unique_ptr<Player>> players;
    players.push_back(std::make_unique<PlayerRandom>());
    players.push_back(std::make_unique<PlayerBestRandom>());

    // create game
    Game game;
    game.newGame();

    while (not game.isGameFinished())
    {
        player_t currentPlayer = game.getCurrentPlayer();
        ThrowParams params = players[currentPlayer]->chooseParams(game);
        game.throwBall(params);

        displayBall("jack", game.getJack());
        displayBalls("red", game.getRedBalls());
        displayBalls("blue", game.getBlueBalls());
    }

    GameResult result = game.computeResult();
    if (result._winningPlayer==PLAYER_RED)
        std::cout << "red win !" << std::endl;
    else
        std::cout << "blue win !" << std::endl;

    return 0;
}

