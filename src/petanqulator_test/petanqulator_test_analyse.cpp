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

void comparerAlgorithme(std::string nomFichier, int nbRun, int lambda){
           
    //choix des algos
    vector<unique_ptr<Player>> players;
    players.push_back(make_unique<PlayerDichotomie>());
    players.push_back(make_unique<PlayerAverageMu>(2.0, lambda));
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

    comparerAlgorithme("analyse/resultat18.csv", 200, 10);
    comparerAlgorithme("analyse/resultat19.csv", 200, 12);
    comparerAlgorithme("analyse/resultat20.csv", 200, 14);
    comparerAlgorithme("analyse/resultat21.csv", 200, 16);
    comparerAlgorithme("analyse/resultat22.csv", 200, 18);
    comparerAlgorithme("analyse/resultat23.csv", 200, 20);
    comparerAlgorithme("analyse/resultat24.csv", 200, 22);
    comparerAlgorithme("analyse/resultat25.csv", 200, 24);
    comparerAlgorithme("analyse/resultat26.csv", 200, 26);
    comparerAlgorithme("analyse/resultat27.csv", 200, 28);    
    comparerAlgorithme("analyse/resultat28.csv", 200, 30);
    
    comparerAlgorithme("analyse/resultat29.csv", 200, 30);
    comparerAlgorithme("analyse/resultat30.csv", 200, 30);
    comparerAlgorithme("analyse/resultat31.csv", 200, 30);
    comparerAlgorithme("analyse/resultat32.csv", 200, 30);
    comparerAlgorithme("analyse/resultat33.csv", 200, 30);
    comparerAlgorithme("analyse/resultat34.csv", 200, 30);
    comparerAlgorithme("analyse/resultat35.csv", 200, 30);
    comparerAlgorithme("analyse/resultat36.csv", 200, 30);
    comparerAlgorithme("analyse/resultat37.csv", 200, 30);
    comparerAlgorithme("analyse/resultat38.csv", 200, 30);    
    comparerAlgorithme("analyse/resultat39.csv", 200, 30);
    comparerAlgorithme("analyse/resultat48.csv", 400, 20);
    
    return 0;
}

