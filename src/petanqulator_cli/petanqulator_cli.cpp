// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include <petanqulator/Player.hpp>

#include <iomanip>

void displayPosition(const GameBall & ball)
{
    btVector3 position = ball._transform.getOrigin();
    std::cout << std::setprecision(2) << '(' << position.getX() 
        << ", " << position.getY() << ", " << position.getZ() << ')';
}

int main()
{
    std::vector<std::unique_ptr<Player>> players;
    players.push_back(std::make_unique<PlayerRandom>());
    //players.push_back(std::make_unique<PlayerRandom>());
    players.push_back(std::make_unique<PlayerBestRandom>());

    // create game
    Game game;
    game.newGame();

    while (not game.isGameFinished())
    {
        // throw ball
        player_t currentPlayer = game.getCurrentPlayer();
        ThrowParams params = players[currentPlayer]->chooseParams(game);
        std::cout << "throw (" << params._pitch << ", " << params._yaw 
            << ", " << params._velocity << ") ";
        if (currentPlayer==PLAYER_RED)
           std::cout << "red" << std::endl;
        else
           std::cout << "blue" << std::endl;
        game.throwBall(params);

        // display jack
        std::cout << "jack ";
        displayPosition(game.getJack());
        std::cout << std::endl;

        // display game results
        GameResult result = game.computeResult();
        for (const auto & r : result._ballResults)
        {
            if (r._player==PLAYER_RED) 
                std::cout << "red ";
            else
                std::cout << "blue ";
            std::cout << std::setprecision(8) << float(r._distanceToJack); 
            if (r._isWinning)
                std::cout << " winning";
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }

    GameResult result = game.computeResult();
    if (result._winningPlayer==PLAYER_RED)
        std::cout << "red win !" << std::endl;
    else if (result._winningPlayer==PLAYER_BLUE)
        std::cout << "blue win !" << std::endl;
    else
        std::cout << "draw !" << std::endl;

    return 0;
}

