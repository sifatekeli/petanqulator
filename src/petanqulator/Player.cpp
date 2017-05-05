// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Player.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <unistd.h>


 
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

double generateNormalDistribution(double mu, double sigma){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<double> normal(mu, sigma);

    return normal(generator);
}


ThrowParams PlayerOnePlusOne::chooseParams(const Game & game) 
{
    

    ThrowParams bestParams = PlayerRandom::chooseParams(game);

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