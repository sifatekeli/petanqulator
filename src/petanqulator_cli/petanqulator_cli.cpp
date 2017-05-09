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
    players.push_back(make_unique<PlayerRandom>());
    players.push_back(make_unique<PlayerBestRandom>());
    players.back()->_params["nbTries"] = 10;

    Game game;

    int nbGames = 100;
    int nbRed = 0;
    int nbBlue = 0;
    int nbDraw = 0;

    for (int i=0; i<nbGames; i++)
    {
        // run game
        game.newGame();
        while (not game.isGameFinished())
        {
            player_t currentPlayer = game.getCurrentPlayer();
            VecParam params = players[currentPlayer]->chooseParams(game);
            game.throwBall(params);

            // ---
            cout << game.getCurrentPlayer() << "          ";
            if(game.getCurrentPlayer() == 0) cout << (game.getRedBalls()[game.getRedBalls().size()]).getPosition() << endl;
            if(game.getCurrentPlayer() == 1) cout << (game.getRedBalls()[game.getBlueBalls().size()]).getPosition() << endl;
            if(game.getCurrentPlayer() == 2) cout << endl;
            /*
            cout << "----------------------------------" << endl;
            for(GameBall g: (game.getRedBalls())){
              cout << game.getCurrentPlayer() << "      "g.getPosition() << endl;
            }*/
            //cout << float((game.getRedBalls()).end()._mass) << endl;
            // ---
        }

        // get result
        GameResult result = game.computeResult();
        if (result._winningPlayer==PLAYER_RED)
            nbRed++;
        else if (result._winningPlayer==PLAYER_BLUE)
            nbBlue++;
        else
            nbDraw++;
    }

    // TODO display player name + params
    cout << "nbGames; nbRed; nbBlue; nbDraw" << endl;
    cout << nbGames << "; " << nbRed << "; " << nbBlue << "; " << nbDraw << endl;

    return 0;
}
