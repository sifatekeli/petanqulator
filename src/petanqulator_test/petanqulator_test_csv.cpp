/* 
 * File:   petanqulator_test_csv.cpp
 * Author: sifa
 *
 * Created on 11 mai 2017, 13:50
 */

#include <petanqulator/Player.hpp>

#include <cassert>
#include <fstream>

using namespace std;

int main(int argc, char ** argv) {
    /*
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " outfile\n";
        exit(-1);
    }
    
    string fileName = argv[1];
    */
    string fileName = "outPlot.csv";
    ofstream file(fileName);
    
    vector<unique_ptr<Player>> players;
    players.push_back(make_unique<PlayerOnePlusOne>());
    
    Game game;
    game.newGame();

    file << "pitch yaw velocity xball yball zball distance xjack yjack zjack \n";
    
    
    for(int i = 0 ; i < 500; i++){
        std::cout << i << std::endl;
        Game testGame(game);
        VecParam params = players[0]->chooseParams(testGame);
        testGame.throwBall(params);
        GameResult result = testGame.computeResult();
        const auto & ball = result._ballResults.back()._position;
        const auto & jack = game.getJack()._transform.getOrigin();
        const auto & distance = result._ballResults.back()._distanceToJack;

        file << params[0] << ' ' << params[1] << ' ' << params[2] << ' ';
        file << ball[0] << ' ' << ball[1] << ' ' << ball[2] << ' ';
        file << distance << ' ';
        file << jack[0] << ' ' << jack[1] << ' ' << jack[2] << ' ';
        file << endl;
        
    }
    return 0;
}


