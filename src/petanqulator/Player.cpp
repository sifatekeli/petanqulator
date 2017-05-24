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


VecParam PlayerRandom::chooseParams(const Game & game) 
{
    VecParam pmin = game.getMinParams();
    VecParam pmax = game.getMaxParams();
    return _prng.generate(pmin, pmax);
}

PlayerBestRandom::PlayerBestRandom()
{
    _params["nbTries"] = 10;
}

VecParam PlayerBestRandom::chooseParams(const Game & game) 
{
    int nbTries = _params["nbTries"];
    VecParam bestParams = PlayerRandom::chooseParams(game);
    player_t currentPlayer = game.getCurrentPlayer();
    for (int i=1; i<nbTries; i++)
    {
        VecParam testParams = PlayerRandom::chooseParams(game);
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

PlayerGoodRandom::PlayerGoodRandom(btScalar precision){
    _precision = precision;
}

VecParam PlayerGoodRandom::chooseParams(const Game & game) 
{
    VecParam bestParams = PlayerRandom::chooseParams(game);
    btScalar precision = 4.0;
    btScalar bestDistanceToJack = 1000.0;
    player_t currentPlayer = game.getCurrentPlayer();

    
    do{
        VecParam testParams = PlayerRandom::chooseParams(game);
        btScalar testDistanceToJack = game.fitness_boule(testParams);
        
        if(testDistanceToJack < bestDistanceToJack){
            bestDistanceToJack = testDistanceToJack;
            bestParams = testParams;
        }

    }while(bestDistanceToJack > _precision);
    return bestParams;
}

PlayerOnePlusOneStatic::PlayerOnePlusOneStatic(int nb_iteration){
    _nb_iteration = nb_iteration;
}

VecParam PlayerOnePlusOneStatic::chooseParams(const Game & game) 
{
    btScalar n_iteration = 0;
    btScalar bestDistanceToJack = 1000.0;

    player_t currentPlayer = game.getCurrentPlayer();
    
    float sigma_pitch = 4.0;
    float sigma_yaw = 4.0;
    float sigma_velocity = 0.5;

    VecParam bestParams = VecParam(0,0,0);
    VecParam testParams = PlayerRandom::chooseParams(game);
    
    do{ 
        do{
            testParams[0] = bestParams[0] + sigma_pitch * _prng.generateNormalDistribution(0.0, 4.0);
        }while(testParams[0] < -90 or testParams[0] > 90);
        do{
            testParams[1] = bestParams[1] + sigma_yaw * _prng.generateNormalDistribution(0.0, 4.0);
        }while(testParams[1] < -180 or testParams[1] > 180);
        do{
            testParams[2] = bestParams[2] + sigma_velocity * _prng.generateNormalDistribution(0.0, 4.0);
        }while(testParams[2] < 0 or testParams[2] > 10);
        btScalar testDistanceToJack = game.fitness_boule(testParams);
        
        if(testDistanceToJack < bestDistanceToJack){
            bestDistanceToJack = testDistanceToJack;
            bestParams = testParams;
        }

        n_iteration++;
        //std::cout << "au pif " << bestDistanceToJack << std::endl;
    }while(n_iteration < _nb_iteration);

    return bestParams;
}

PlayerOnePlusOneStaticSmart::PlayerOnePlusOneStaticSmart(int nb_iteration){
    _nb_iteration = nb_iteration;
}

VecParam PlayerOnePlusOneStaticSmart::chooseParams(const Game & game) 
{
    btScalar n_iteration = 0;
    btScalar bestDistanceToJack = 1000000.0;

    player_t currentPlayer = game.getCurrentPlayer();
    
    float sigma_pitch = 4.0;
    float sigma_yaw = 4.0;
    float sigma_velocity = 0.5;

    VecParam bestParams = VecParam(0,0,0);
    VecParam testParams = PlayerRandom::chooseParams(game);
    
    do{ 
        do{
            testParams[0] = bestParams[0] + sigma_pitch * _prng.generateNormalDistribution(0.0, 4.0);
        }while(testParams[0] < -90 or testParams[0] > 90);
        do{
            testParams[1] = bestParams[1] + sigma_yaw * _prng.generateNormalDistribution(0.0, 4.0);
        }while(testParams[1] < -180 or testParams[1] > 180);
        do{
            testParams[2] = bestParams[2] + sigma_velocity * _prng.generateNormalDistribution(0.0, 4.0);
        }while(testParams[2] < 0 or testParams[2] > 10);
        
        btScalar testDistanceToJack = game.fitness(testParams);
        
        if(testDistanceToJack < bestDistanceToJack){
            bestDistanceToJack = testDistanceToJack;
            bestParams = testParams;
        }

        n_iteration++;
    }while(n_iteration < _nb_iteration);
    std::cout << bestDistanceToJack << std::endl;

    return bestParams;
}

PlayerOnePlusOneDynamic::PlayerOnePlusOneDynamic(btScalar precision, int compteur){
    _precision = precision;
    _compteur = compteur;
}

VecParam PlayerOnePlusOneDynamic::chooseParams(const Game & game) 
{       
    float sigmaF = 100;
    btScalar bestDistanceToJack = 1000.0;
    VecParam bestParams = PlayerRandom::chooseParams(game);
    int compteur = _compteur; // Compteur qui arrêtera la boucle si pendant _compteur iterations aucune amelioration n'est trouvée
    
    do{
        VecParam testParams;
        if (sigmaF < 0.001) {
                // Eviter les optimums locaux
                sigmaF = 100;
        } else {
                do{
                    testParams[0] = bestParams[0] + sigmaF * _prng.generateNormalDistribution(0.0, 1.0);
                }while(testParams[0] < -90 or testParams[0] > 90);
                do{
                    testParams[1] = bestParams[1] + sigmaF * _prng.generateNormalDistribution(0.0, 1.0);
                }while(testParams[1] < -180 or testParams[1] > 180);
                do{
                    testParams[2] = bestParams[2] + sigmaF * _prng.generateNormalDistribution(0.0, 1.0);
                }while(testParams[2] < 0 or testParams[2] > 10);                
        }

        btScalar testDistanceToJack = game.fitness_boule(testParams);
        
        if(testDistanceToJack < bestDistanceToJack){ // Si le lancé de test est meilleur que le best
            bestDistanceToJack = testDistanceToJack; 
            bestParams = testParams;
            
            sigmaF = sigmaF * exp(1.0/3.0);
            compteur = 0;
        }else{ // Si le lancé de test n'est pas meilleur que le best
            sigmaF = sigmaF / std::pow(exp(1.0/3.0),0.25);
            compteur++;
        }
    }while(bestDistanceToJack >= _precision && compteur < _compteur); 
    // On s'arrête si on obtient un résultat satisfaisant ou si le compteur arrive à 0
    return bestParams;
}

PlayerOnePlusOneDynamicSmart::PlayerOnePlusOneDynamicSmart(btScalar precision, int compteur){
    _precision = precision;
    _compteur = compteur;
}

VecParam PlayerOnePlusOneDynamicSmart::chooseParams(const Game & game) 
{       
    float sigmaF = 100;
    btScalar bestDistanceToJack = 1000000.0;
    VecParam bestParams = PlayerRandom::chooseParams(game);
    int compteur = _compteur; // Compteur qui arrêtera la boucle si pendant _compteur iterations aucune amelioration n'est trouvée
    
    do{
        VecParam testParams;
        if (sigmaF < 0.001) {
                // Eviter les optimums locaux
                sigmaF = 100;
        } else {
                do{
                    testParams[0] = bestParams[0] + sigmaF * _prng.generateNormalDistribution(0.0, 1.0);
                }while(testParams[0] < -90 or testParams[0] > 90);
                do{
                    testParams[1] = bestParams[1] + sigmaF * _prng.generateNormalDistribution(0.0, 1.0);
                }while(testParams[1] < -180 or testParams[1] > 180);
                do{
                    testParams[2] = bestParams[2] + sigmaF * _prng.generateNormalDistribution(0.0, 1.0);
                }while(testParams[2] < 0 or testParams[2] > 10);                
        }

        btScalar testDistanceToJack = game.fitness(testParams);
        
        if(testDistanceToJack < bestDistanceToJack){ // Si le lancé de test est meilleur que le best
            bestDistanceToJack = testDistanceToJack; 
            bestParams = testParams;
            
            sigmaF = sigmaF * exp(1.0/3.0);
            compteur = 0;
        }else{ // Si le lancé de test n'est pas meilleur que le best
            sigmaF = sigmaF / std::pow(exp(1.0/3.0),0.25);
            compteur++;
        }
    }while(bestDistanceToJack >= _precision && compteur < _compteur); 
    // On s'arrête si on obtient un résultat satisfaisant ou si le compteur arrive à 0
    return bestParams;
}

struct comp
{
    int operator()(const std::pair<double,VecParam>& t1,const std::pair<double,VecParam>& t2) const
        {
            return t1.first<t2.first;
        }
};

PlayerAverageMu::PlayerAverageMu(btScalar precision, int lambdaSize){
    _precision = precision;
    _lambdaSize = lambdaSize;
    _muSize = lambdaSize / 4;
}

VecParam PlayerAverageMu::chooseParams(const Game & game) 
{
    player_t currentPlayer = game.getCurrentPlayer();
    VecParam bestParams = PlayerRandom::chooseParams(game);
    VecParam testParams;
    VecParam finalParams;
    
    float sigma_pitch = 20.0;
    float sigma_yaw = 20.0;
    float sigma_velocity = 2.5;
    
    btScalar bestDistanceToJack = 1000.0;
    btScalar testDistanceToJack = 1000.0;
    
    // Pour que l'algo s'arrête s'il ne trouve pas de meilleur solution durant nb_iteration iterations
    int nb_iteration = 100;
    int compteur = 0;

    do{
        std::vector<std::pair<double,VecParam>> solutions (_lambdaSize);

        for(int i = 0; i < _lambdaSize; i++){
            do{
                testParams[0] = bestParams[0] + sigma_pitch * _prng.generateNormalDistribution(0.0, 1.0);
            }while(testParams[0] < -90 or testParams[0] > 90);
            do{
                testParams[1] = bestParams[1] + sigma_yaw * _prng.generateNormalDistribution(0.0, 1.0);
            }while(testParams[1] < -180 or testParams[1] > 180);
            do{
                testParams[2] = bestParams[2] + sigma_velocity * _prng.generateNormalDistribution(0.0, 1.0);
            }while(testParams[2] < 0 or testParams[2] > 10);

            btScalar testDistanceToJack = game.fitness_boule(testParams);
            solutions[i] = std::make_pair(testDistanceToJack, testParams);
        }

        std::sort(solutions.begin(), solutions.end(), comp());

        solutions.resize(_muSize);
        
        double sum_pitch = 0;
        double sum_yaw = 0;
        double sum_velocity = 0;
            
        for(int i = 0 ; i < _muSize; i++){
            sum_pitch += solutions[i].second[0];
            sum_yaw += solutions[i].second[1];
            sum_velocity += solutions[i].second[2];
        }
        
        bestParams[0] = sum_pitch / _muSize;
        bestParams[1] = sum_yaw / _muSize;
        bestParams[2] = sum_velocity / _muSize; 

        bestDistanceToJack = game.fitness_boule(bestParams);
        if(bestDistanceToJack < testDistanceToJack){
            compteur = 0;
            testDistanceToJack = bestDistanceToJack;
            finalParams = bestParams;
        }else{
            compteur++;
        }

    }while(bestDistanceToJack >= _precision && compteur < nb_iteration);

    return finalParams;
}

PlayerAverageMuSmart::PlayerAverageMuSmart(btScalar precision, int lambdaSize){
    _precision = precision;
    _lambdaSize = lambdaSize;
    _muSize = lambdaSize / 4;
}

VecParam PlayerAverageMuSmart::chooseParams(const Game & game) 
{
    player_t currentPlayer = game.getCurrentPlayer();
    VecParam bestParams = PlayerRandom::chooseParams(game);
    VecParam testParams;
    
    float sigma_pitch = 20.0;
    float sigma_yaw = 20.0;
    float sigma_velocity = 2.5;
    
    btScalar bestDistanceToJack = 1000000.0;
    btScalar testDistanceToJack = 1000000.0;
    
    // Pour que l'algo s'arrête s'il ne trouve pas de meilleur solution durant nb_iteration iterations
    int nb_iteration = 100;
    int compteur = 0;
    
    do{
        std::vector<std::pair<double,VecParam>> solutions (_lambdaSize);

        for(int i = 0; i < _lambdaSize; i++){
            do{
                testParams[0] = bestParams[0] + sigma_pitch * _prng.generateNormalDistribution(0.0, 1.0);
            }while(testParams[0] < -90 or testParams[0] > 90);
            do{
                testParams[1] = bestParams[1] + sigma_yaw * _prng.generateNormalDistribution(0.0, 1.0);
            }while(testParams[1] < -180 or testParams[1] > 180);
            do{
                testParams[2] = bestParams[2] + sigma_velocity * _prng.generateNormalDistribution(0.0, 1.0);
            }while(testParams[2] < 0 or testParams[2] > 10);

            btScalar testDistanceToJack = game.fitness_boule(testParams);
            solutions[i] = std::make_pair(testDistanceToJack, testParams);
        }

        std::sort(solutions.begin(), solutions.end(), comp());

        solutions.resize(_muSize);
        
        double sum_pitch = 0;
        double sum_yaw = 0;
        double sum_velocity = 0;
            
        for(int i = 0 ; i < _muSize; i++){
            sum_pitch += solutions[i].second[0];
            sum_yaw += solutions[i].second[1];
            sum_velocity += solutions[i].second[2];
        }
        
        bestParams[0] = sum_pitch / _muSize;
        bestParams[1] = sum_yaw / _muSize;
        bestParams[2] = sum_velocity / _muSize; 

        bestDistanceToJack = game.fitness(bestParams);
        
        if(bestDistanceToJack < testDistanceToJack){
            compteur = 0;
            testDistanceToJack = bestDistanceToJack;
        }else{
            compteur++;
        }
        
    }while(bestDistanceToJack >= _precision && compteur < nb_iteration);

    return bestParams;
}

VecParam PlayerDichotomie::chooseParams(const Game & game)
{
    
    VecParam bestParams = PlayerRandom::chooseParams(game);
    VecParam testParams;
    player_t currentPlayer = game.getCurrentPlayer();
    //GameResult result;    

    std::vector<double> distance;
    std::vector<double> distanceTrier;
    std::vector<int> degreeDistance = {-180, -60, 60, 180};
    double distanceMinIntermediaire=0.0;
    double best = 1000.0;
    int nbIterations=0;
    
    //initialise les deux autres parametres
    testParams[0] = 32.0;
    testParams[2] = 2.0;
  
    //***************************************  OPTIMISATION SUR YAW   ******************************************************
    testParams[1] = -180.0;

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
         testParams[1] += 120; 
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
         testParams[1] = (degreeDistance[0]+degreeDistance[1] )/2 ;
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
         degreeDistance.push_back(testParams[1]);
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
    testParams[0]=0;

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
        degreeDistance.push_back(testParams[0]);
        testParams[0] += 90;
    }
            
    //DICHOTOMIE 10 itérations sans amélioration = STOP !!!
   nbIterations=0;
   while(nbIterations<10){
       
       //dichotomie
       testParams[0] = (degreeDistance[0]+degreeDistance[1] )/2 ;

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
       degreeDistance.push_back(testParams[0]);
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
    testParams[2]=0.0;

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
        degreeDistance.push_back(testParams[2]);
        testParams[2] += 10.0;
    }

     nbIterations=0;
    //DICHOTOMIE 10 itérations sans amélioration = STOP !!!
    while(nbIterations<10){

        //dichotomie
        testParams[2] = (degreeDistance[0]+degreeDistance[1] )/2 ;

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
        degreeDistance.push_back(testParams[2]);
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

