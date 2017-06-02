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

void comparerAlgorithmeSmart(std::string nomFichier, int nbRun, int lambda){
            
    //choix des algos
    vector<unique_ptr<Player>> players;   
    players.push_back(make_unique<PlayerOnePlusOneStaticSmart>(200));
    players.push_back(make_unique<PlayerAverageMuSmart>(0.8,lambda));
    

    players.back()->_params["nbTries"] = 1;
    
    int bleu=0;
    int rouge=0;

    std::ofstream flux(nomFichier.c_str());
     
    //Ecriture fichier
    if(flux){
        
        //nombre de run
        for (int i = 0; i < nbRun; i++) {
            
            bleu=0;
            rouge=0;
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

            if(result._winningPlayer == 0){
                rouge = result._nbWinningBalls;
            }else{
                bleu = result._nbWinningBalls;
            }
            flux << rouge << " " << bleu << "\n";
        }   
    }else{
        std::cout << "Erreur d'écriture" << std::endl;
    }
}

int main(){

//    partieEnCours("fichier");
//    comparerAlgorithme("analyse/Resultat48bis.csv",400,20);
    comparerAlgorithmeSmart("analyse/Resultat61.csv",400,20);
    
    return 0;
}

