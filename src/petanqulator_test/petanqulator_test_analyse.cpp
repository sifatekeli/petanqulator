/* 
 * File:   petanqulator_test_analyse.cpp
 * Author: kevin
 * 
 * Created on 11 mai 2017, 13:33
 */

#include <petanqulator/Player.hpp>

#include <iomanip>
#include <fstream>

using namespace std;

void displayPosition(const GameBall & ball)
{
    std::cout << ball._transform.getOrigin();
}

void comparerAlgorithme(std::string nomFichier, int nbRun){
           
    //choix des algos
    vector<unique_ptr<Player>> players;
    players.push_back(make_unique<PlayerDichotomie>());
    players.push_back(make_unique<PlayerAverageMu>(2.0, 12, 7));
    players.back()->_params["nbTries"] = 1;
    

    std::ofstream flux(nomFichier.c_str());
     
    //Ecriture fichier
    if(flux){
        
        //nombre de run
        for (int i = 0; i < nbRun; i++) {
            
            std::cout << i << std::endl;
            
            // create game
            Game game;
            game.newGame();
            
            while (not game.isGameFinished()){
                // throw ball
                player_t currentPlayer = game.getCurrentPlayer();
                VecParam params = players[currentPlayer]->chooseParams(game);
                game.throwBall(params); 
            }
            GameResult result = game.computeResult();
            
            //ecriture dans le flux
            for(double n : game.bestDistancePlayer(result) ){
                flux << n << " ";
            }
            flux << "\n";
        }   
    }else{
        std::cout << "Erreur d'écriture" << std::endl;
    }
    
}

int main(){

    comparerAlgorithme("resultat19.csv",200);
    
    return 0;
}