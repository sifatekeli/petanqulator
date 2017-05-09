// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Player.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <math.h>  
#include <fstream>
#include <unistd.h>
#include <bullet/LinearMath/btScalar.h>


ThrowParams PlayerRandom::chooseParams(const Game & game) 
{
    ThrowParams pmin = game.getMinParams();
    ThrowParams pmax = game.getMaxParams();
    double pitch = _prng.generate(pmin._pitch, pmax._pitch);
    double yaw = _prng.generate(pmin._yaw, pmax._yaw);
    double velocity = _prng.generate(pmin._velocity, pmax._velocity);
    /*
    double pitch = _prng.generate(0, 70);
    double yaw = _prng.generate(-90, 90);
    double velocity = _prng.generate(1, 7);
    */
    return ThrowParams {pitch, yaw, velocity};
}

PlayerBestRandom::PlayerBestRandom()
{
    _params["nbTries"] = 10;
}

ThrowParams PlayerBestRandom::chooseParams(const Game & game) 
{
    int nbTries = _params["nbTries"];
    ThrowParams bestParams = PlayerRandom::chooseParams(game);
    player_t currentPlayer = game.getCurrentPlayer();
    for (int i=1; i<nbTries; i++)
    {
        ThrowParams testParams = PlayerRandom::chooseParams(game);
        Game testGame(game);
        testGame.throwBall(testParams);
        GameResult result = testGame.computeResult();
        if (result._winningPlayer == currentPlayer)
            bestParams = testParams;
        // TODO test other reward policy (nb winning balls, min distance...)

#ifdef LOG
        std::cout << testParams; 
        if (result._winningPlayer == currentPlayer)
        {
        const BallResult & br = result._ballResults.front();
            std::cout << " better"
                << " " << br._position
                << " " << std::setprecision(4) << br._distanceToJack;
        }
        std::cout << std::endl;
#endif

    }

    return bestParams;
}

ThrowParams PlayerGoodRandom::chooseParams(const Game & game) 
{
    ThrowParams bestParams = PlayerRandom::chooseParams(game);
    
    btScalar precision = 4.0;
    btScalar bestDistanceToJack = 1000;
    player_t currentPlayer = game.getCurrentPlayer();

    
    do{
        ThrowParams testParams = PlayerRandom::chooseParams(game);
        
        Game testGame(game);
        testGame.throwBall(testParams);
        GameResult result = testGame.computeResult();

        // Met la balle qui vient d'être lancée par le joueur courant dans la variable br
        GameBall gb = testGame.getPlayerBalls(currentPlayer).back();
        BallResult br;
        for (BallResult & b : result._ballResults) {
            if(b._position == gb.getPosition()){
                br = b;
            }
        }
        btScalar testDistanceToJack = br._distanceToJack;
        
        
        if(testDistanceToJack < bestDistanceToJack){
            bestDistanceToJack = testDistanceToJack;
            bestParams = testParams;
            
        }

    }while(bestDistanceToJack > precision);
    return bestParams;
}

ThrowParams PlayerMarcheAleatoire::chooseParams(const Game & game) 
{
    btScalar nb_iter = 500.0;
    btScalar bestDistanceToJack = 1000.0;

    player_t currentPlayer = game.getCurrentPlayer();
    
    float sigma_pitch = 4.0;
    float sigma_yaw = 4.0;
    float sigma_velocity = 0.5;

    ThrowParams bestParams;
    ThrowParams testParams = PlayerRandom::chooseParams(game);
    
    do{ 
        testParams._pitch += sigma_pitch * _prng.generateNormalDistribution(0.0, 4.0);
        testParams._yaw += sigma_yaw * _prng.generateNormalDistribution(0.0, 4.0);
        testParams._velocity += sigma_velocity * _prng.generateNormalDistribution(0.0, 4.0);
        
        // Lancer test        
        Game testGame(game);
        testGame.throwBall(testParams);
        GameResult result = testGame.computeResult();
                
        // Met la balle qui vient d'être lancée par le joueur courant dans la variable br
        GameBall gb = testGame.getPlayerBalls(currentPlayer).back();
        BallResult br;
        for (BallResult & b : result._ballResults) {
            if(b._position == gb.getPosition()){
                br = b;
            }
        }
        
        btScalar testDistanceToJack = br._distanceToJack;
        
        if(testDistanceToJack < bestDistanceToJack){
            bestDistanceToJack = testDistanceToJack; 
            bestParams = testParams;
        }
        
        nb_iter--;
    }while(nb_iter >= 0);
    
    return bestParams;
}


ThrowParams PlayerOnePlusOne::chooseParams(const Game & game) 
{
    double bestDistance = 1000;
    double testDistance;
    
    float sigma_pitch = 20.0;
    float sigma_yaw = 20.0;
    float sigma_velocity = 2.5;

    btScalar bestDistanceToJack = 1000.0;
    btScalar precision = 4.0;
        
    player_t currentPlayer = game.getCurrentPlayer();
    ThrowParams bestParams = PlayerRandom::chooseParams(game);
    
    // Compteur qui arrêtera la boucle si pendant 200 iterations aucune amelioration n'est trouvée
    int compteur = 200;
    
    do{
        ThrowParams testParams;
        if (sigma_pitch < 0.01 or sigma_yaw < 0.01 or sigma_velocity < 0.01) {
                // Eviter les optimums locaux
                sigma_pitch = 20.0;
                sigma_yaw = 20.0;
                sigma_velocity = 2.5;
                
                testParams._pitch = _prng.generate(-90,90);
                testParams._yaw = _prng.generate(-180,180);
                testParams._velocity = _prng.generate(0,10);  
        } else {
                // Modifie les parametres de lancé
                testParams._pitch = bestParams._pitch + sigma_pitch * _prng.generateNormalDistribution(0.0, 1.0);
                testParams._yaw = bestParams._yaw + sigma_yaw * _prng.generateNormalDistribution(0.0, 1.0);
                testParams._velocity = bestParams._velocity + _prng.generateNormalDistribution(0.0, 1.0);
        }
        
        // Crée une copie du jeu et fait le lancé
        Game testGame(game);
        testGame.throwBall(testParams);
        GameResult result = testGame.computeResult();
        
        // Met la balle qui vient d'être lancée par le joueur courant dans la variable br
        GameBall gb = testGame.getPlayerBalls(currentPlayer).back();
        BallResult br;
        for (BallResult & b : result._ballResults) {
            if(b._position == gb.getPosition()){
                br = b;
            }
        }
        
        if(br._distanceToJack < bestDistanceToJack){ // Si le lancé de test est meilleur que le best
            bestDistanceToJack = br._distanceToJack; 
            bestParams = testParams;
            
            // MAJ des sigmas
            sigma_pitch = sigma_pitch * exp(1.0/3.0);
            sigma_yaw = sigma_yaw * exp(1.0/3.0);
            sigma_velocity = sigma_velocity * exp(1.0/3.0);
            
            compteur = 200;
        }else{ // Si le lancé de test n'est pas meilleur que le best
            // MAJ des sigmas
            sigma_pitch = sigma_pitch / std::pow(exp(1.0/3.0),0.25);
            sigma_yaw = sigma_yaw / std::pow(exp(1.0/3.0),0.25);
            sigma_velocity = sigma_velocity / std::pow(exp(1.0/3.0),0.25);
        }
        compteur--;
        
    }while(bestDistanceToJack >= precision && compteur >=0); 
    // On s'arrête si on obtient un résultat satisfaisant ou si le compteur arrive à 0

    return bestParams;
}







ThrowParams PlayerDichotomie::chooseParams(const Game & game)
{
    
    ThrowParams bestParams = PlayerRandom::chooseParams(game);
    ThrowParams testParams;
    player_t currentPlayer = game.getCurrentPlayer();
    //GameResult result;    

    std::vector<double> distance;
    std::vector<double> distanceTrier;
    std::vector<int> degreeDistance = {-180, -60, 60, 180};
    double distanceMinIntermediaire=0.0;
    double best = 1000.0; 
    int nbIterations=0;
    
    //initialise les deux autres parametres
    testParams._pitch = 32.0;
    testParams._velocity = 2.0;
  
    //***************************************  OPTIMISATION SUR YAW   ******************************************************
    testParams._yaw = -180.0;

    //4 points : -180, -60, 60, 180
     for(int i=0; i<4; i++){
         Game testGame(game);
         testGame.throwBall(testParams);
         GameResult result = testGame.computeResult();
         
         //DISTANCE TO JACK
         GameBall gb = testGame.getPlayerBalls(currentPlayer).back();
         BallResult br;
         for (BallResult & b : result._ballResults) {
             if(b._position == gb.getPosition()){
                 br = b;
             }
         }
        //FIN DISTANCE TO JACK
         
         distance.push_back(br._distanceToJack);
         testParams._yaw += 120; 
     }

     //trie par borne inf et borne sup
     std::vector<double>::iterator result = std::min_element(std::begin(distance), std::end(distance));

     // borne inférieur
     distanceTrier.push_back(distance[std::distance(std::begin(distance), result)]);
     std::swap(degreeDistance[0],degreeDistance[std::distance(std::begin(distance), result)]);  
     distance[std::distance(std::begin(distance), result)]=1000.0;

     //borne supérieur
     result = std::min_element(std::begin(distance), std::end(distance));
     distanceTrier.push_back(distance[std::distance(std::begin(distance), result)]);
     std::swap(degreeDistance[1],degreeDistance[std::distance(std::begin(distance), result)]);

     //Nettoyage des valeurs inutiles
     degreeDistance.erase(degreeDistance.begin()+3);
     degreeDistance.erase(degreeDistance.begin()+2);


     //DICHOTOMIE 10 itérations sans amélioration = STOP !!!
     while(nbIterations<10){

         //dichotomie
         testParams._yaw = (degreeDistance[0]+degreeDistance[1] )/2 ;
         Game testGame(game);
         testGame.throwBall(testParams);
         GameResult result = testGame.computeResult();

         //DISTANCE TO JACK
         GameBall gb = testGame.getPlayerBalls(currentPlayer).back();
         BallResult br;
         for (BallResult & b : result._ballResults) {
             if(b._position == gb.getPosition()){
                 br = b;
             }
         }
        //FIN DISTANCE TO JACK

         distanceTrier.push_back(br._distanceToJack);

         //borne supérieur
         std::vector<double>::iterator resultTrier = std::min_element(std::begin(distanceTrier), std::end(distanceTrier));
         degreeDistance.push_back(testParams._yaw);
         std::swap(distanceTrier[0],distanceTrier[std::distance(std::begin(distanceTrier), resultTrier)]);
         std::swap(degreeDistance[0],degreeDistance[std::distance(std::begin(distanceTrier), resultTrier)]);
         distanceMinIntermediaire = distanceTrier[0];

         distanceTrier[0]=1000.0;

         //borne superieur
         resultTrier = std::min_element(std::begin(distanceTrier), std::end(distanceTrier));
         std::swap(distanceTrier[1],distanceTrier[std::distance(std::begin(distanceTrier), resultTrier)]);
         std::swap(degreeDistance[1],degreeDistance[std::distance(std::begin(distanceTrier), resultTrier)]);

         //Nettoie le tableau
         degreeDistance.erase(degreeDistance.begin()+2);
         distanceTrier.erase(distanceTrier.begin()+2);
         distanceTrier[0]= distanceMinIntermediaire;

         //Stoke le meilleur
         if(br._distanceToJack < best){
             best = br._distanceToJack;
             bestParams = testParams;
             nbIterations=1;
         }
         nbIterations++;  
     } 
        
    // *************************************OPTIMISATION PITCH************************************************ 
    testParams = bestParams;
       
    distanceTrier.clear();
    degreeDistance.clear();
    testParams._pitch=0;

    //init bornes : 0 et 90
    for(int i=0; i<2; i++){
        Game testGame(game);
        testGame.throwBall(testParams);
        GameResult result = testGame.computeResult();

        //DISTANCE TO JACK
        GameBall gb = testGame.getPlayerBalls(currentPlayer).back();
        BallResult br;
        for (BallResult & b : result._ballResults) {
            if(b._position == gb.getPosition()){
                br = b;
            }
        }
       //FIN DISTANCE TO JACK

        distance.push_back(br._distanceToJack);
        distanceTrier.push_back(br._distanceToJack);
        degreeDistance.push_back(testParams._pitch);
        testParams._pitch += 90;
    }
            
    //DICHOTOMIE 10 itérations sans amélioration = STOP !!!
   nbIterations=0;
   while(nbIterations<10){
       
       //dichotomie
       testParams._pitch = (degreeDistance[0]+degreeDistance[1] )/2 ;

       Game testGame(game);
       testGame.throwBall(testParams);
       GameResult result = testGame.computeResult();
        //DISTANCE TOJACK
       GameBall gb = testGame.getPlayerBalls(currentPlayer).back();
       BallResult br;
       for (BallResult & b : result._ballResults) {
           if(b._position == gb.getPosition()){
               br = b;
           }
       }
      //FIN DISTANCE TO JACK

       distanceTrier.push_back(br._distanceToJack);

       //borne supérieur
       std::vector<double>::iterator resultTrier = std::min_element(std::begin(distanceTrier), std::end(distanceTrier));
       degreeDistance.push_back(testParams._pitch);
       std::swap(distanceTrier[0],distanceTrier[std::distance(std::begin(distanceTrier), resultTrier)]);
       std::swap(degreeDistance[0],degreeDistance[std::distance(std::begin(distanceTrier), resultTrier)]);
       distanceMinIntermediaire = distanceTrier[0];

       distanceTrier[0]=1000.0;

       //borne superieur
       resultTrier = std::min_element(std::begin(distanceTrier), std::end(distanceTrier));
       std::swap(distanceTrier[1],distanceTrier[std::distance(std::begin(distanceTrier), resultTrier)]);
       std::swap(degreeDistance[1],degreeDistance[std::distance(std::begin(distanceTrier), resultTrier)]);

       //Nettoie le tableau
       degreeDistance.erase(degreeDistance.begin()+2);
       distanceTrier.erase(distanceTrier.begin()+2);
       distanceTrier[0]= distanceMinIntermediaire;

       //Stocke le meilleur
       if(br._distanceToJack < best){
           best = br._distanceToJack;
           bestParams = testParams;
           nbIterations=1;
       }
       nbIterations++;  
   }     
       
    // *************************************OPTIMISATION VELOCITY************************************************* 
    
    distanceTrier.clear();
    degreeDistance.clear();
    testParams = bestParams;
    testParams._velocity=0.0;

    //init born
    for(int i=0; i<2; i++){
        Game testGame(game);
        testGame.throwBall(testParams);
        GameResult result = testGame.computeResult();

        //DISTANCE TO JACK
        GameBall gb = testGame.getPlayerBalls(currentPlayer).back();
        BallResult br;
        for (BallResult & b : result._ballResults) {
            if(b._position == gb.getPosition()){
                br = b;
            }
        }
       //FIN DISTANCE TO JACK

        distance.push_back(br._distanceToJack);

        distanceTrier.push_back(br._distanceToJack);
        degreeDistance.push_back(testParams._velocity);
        testParams._velocity += 10.0;
    }

     nbIterations=0;
    //DICHOTOMIE 10 itérations sans amélioration = STOP !!!
    while(nbIterations<10){

        //dichotomie
        testParams._velocity = (degreeDistance[0]+degreeDistance[1] )/2 ;

        Game testGame(game);
        testGame.throwBall(testParams);
        GameResult result = testGame.computeResult();
         //DISTANCE TOJACK
        GameBall gb = testGame.getPlayerBalls(currentPlayer).back();
        BallResult br;
        for (BallResult & b : result._ballResults) {
            if(b._position == gb.getPosition()){
                br = b;
            }
        }
       //FIN DISTANCE TO JACK

        distanceTrier.push_back(br._distanceToJack);

        //borne supérieur
        std::vector<double>::iterator result2 = std::min_element(std::begin(distanceTrier), std::end(distanceTrier));
        degreeDistance.push_back(testParams._velocity);
        std::swap(distanceTrier[0],distanceTrier[std::distance(std::begin(distanceTrier), result2)]);
        std::swap(degreeDistance[0],degreeDistance[std::distance(std::begin(distanceTrier), result2)]);
        distanceMinIntermediaire = distanceTrier[0];

        distanceTrier[0]=1000.0;

        //borne superieur
        result2 = std::min_element(std::begin(distanceTrier), std::end(distanceTrier));
        std::swap(distanceTrier[1],distanceTrier[std::distance(std::begin(distanceTrier), result2)]);
        std::swap(degreeDistance[1],degreeDistance[std::distance(std::begin(distanceTrier), result2)]);

        //Nettoie le tableau
        degreeDistance.erase(degreeDistance.begin()+2);
        distanceTrier.erase(distanceTrier.begin()+2);
        distanceTrier[0]= distanceMinIntermediaire;

        //Prend le meilleur
        if(br._distanceToJack < best){
            best = br._distanceToJack;
            bestParams = testParams;
            nbIterations=1;
        }
        nbIterations++;  
    }  
    
    return bestParams;
 
}