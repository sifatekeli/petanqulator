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
    vector<unique_ptr<Player>> players;
    players.push_back(make_unique<PlayerAverageMu>());
    players.push_back(make_unique<PlayerMarcheAleatoire>());
    players.back()->_params["nbTries"] = 1;

    // create game
    Game game;
    game.newGame();

    while (not game.isGameFinished())
    {
        // throw ball
        player_t currentPlayer = game.getCurrentPlayer();
        ThrowParams params = players[currentPlayer]->chooseParams(game);
        cout << "throw (" << params._pitch << ", " << params._yaw 
            << ", " << params._velocity << ") ";
        if (currentPlayer==PLAYER_RED)
           cout << "red" << endl;
        else
           cout << "blue" << endl;
        game.throwBall(params);

        // display jack
        cout << "jack ";
        displayPosition(game.getJack());
        cout << endl;
        // display game results
        GameResult result = game.computeResult();
        for (const auto & r : result._ballResults)
        {
            if (r._player==PLAYER_RED) 
                cout << "red ";
            else
                cout << "blue ";
            cout << r._position;
            cout << ' ' << setprecision(2) << float(r._distanceToJack); 
            if (r._isWinning)
                cout << " winning";
            cout << endl;
        }
        
//        cout << "\n----------FITNESS----------------" << endl;
//        game.fitness(result);
//        cout << "--------------------------" << endl;

        cout << endl;
    }

    GameResult result = game.computeResult();
    if (result._winningPlayer==PLAYER_RED)
        cout << "red win !" << endl;
    else if (result._winningPlayer==PLAYER_BLUE)
        cout << "blue win !" << endl;
    else
        cout << "draw !" << endl;

    return 0;
}