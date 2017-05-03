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

PlayerOnePlusOne::PlayerOnePlusOne()
{
    _params["nbTries"] = 10;
}

ThrowParams PlayerOnePlusOne::chooseParams(const Game & game) 
{
    
    int nbTries = _params["nbTries"];

    ThrowParams bestParams = PlayerRandom::chooseParams(game);
    ThrowParams bestParams2 = PlayerRandom::chooseParams(game);
    double bestDistanceToJack = 1000.0;

    player_t currentPlayer = game.getCurrentPlayer();
    double precision = 10.0;
    
    float sigma_pitch = 4.5;
    float sigma_yaw = 4.0;
    float sigma_velocity = 2.0;
    
    
    GameResult result;    

    std::cout << "##### \t# " << bestParams._pitch << "\t# " << bestParams._yaw << "\t# " << bestParams._velocity << std::endl;
   
 
    //VARIABLES POUR ALGO
    std::vector<double> distance;
    std::vector<double> distanceTrier;
    std::vector<double> trace;
    std::vector<int> degreeDistance = {-180, -60, 60, 180};
    double distanceMinIntermediaire=0.0;
//    std::cout << "Nombre1 : " << std::setprecision(3) << nombre1 << std::endl;
    
    
    ThrowParams testParams;
    ThrowParams testParams2;
    
    Prng randomYaw;
    Prng randomPitch;
    Prng randomVelocity;

    testParams._yaw = randomYaw.generate(-90,130);
    testParams._pitch = randomPitch.generate(-40,40);
    testParams._velocity = randomVelocity.generate(0,10);
    testParams._pitch = 32.0;
    testParams._velocity = 3.0;
    

    std::cout << "!!!!!!**" << testParams._yaw << " " << testParams._pitch  << " " << testParams._velocity << std::endl;
    
    double best = 1000.0; 
    double best2 = 1000.0;
    
    
    //POUR TESTER GROS PROBLEME !!!
    for(double i=-180.0; i<180.0; i+=1.0){
       testParams._yaw=i;
       Game testGame(game);
       testGame.throwBall(testParams);
       GameResult result = testGame.computeResult();
       
       //position cochonnet
       GameBall positionJack = testGame.getJack();
       std::cout << testParams._yaw << "--->" << std::setprecision(12) << result._ballResults[currentPlayer]._distanceToJack << "  --->   " <<  testParams << "  Position boule : " << result._ballResults[currentPlayer]._position << "    Cochonnet : " << positionJack._transform.getOrigin() <<  std::endl;
    }
    //FIN TEST
    
    
    /*
    for(double i=-180.0; i<180.0; i+=1.0){
       testParams._yaw=i;
       
       Game testGame(game);
       testGame.throwBall(testParams);
       GameResult result = testGame.computeResult();
       
       GameBall positionJack = testGame.getJack();
       std::cout << testParams._yaw << "--->" << std::setprecision(12) << result._ballResults[currentPlayer]._distanceToJack << "  --->   " <<  testParams << "  Position boule : " << result._ballResults[currentPlayer]._position << "    Cochonnet : " << positionJack._transform.getOrigin() <<  std::endl;       
       
       if(result._ballResults[currentPlayer]._distanceToJack < best){
           best = result._ballResults[currentPlayer]._distanceToJack;
           bestParams = testParams;
       }
       
       //OPTIMISATION ALGO QUI DEVRAIT MARCHER MAIS QUI A DU MAL
       if (i==179) {
           
           //INIT POUR TESTER
           testParams2._pitch = 32.0;
           testParams2._velocity = 6.0;
           
           std::cout << " ***************************************OUIIIIIIIII********************************************* " << std::endl;
           testParams2._yaw = randomYaw.generate(-180,180);
           //DEBUT DU TEST QUI TEST QUI SERT PRESQUE A RIEN
           for (int k = 0; k < 2; k++) {
                Game testGame(game);
                testGame.throwBall(testParams2);
                GameResult result = testGame.computeResult(); 
                std::cout << testParams2._yaw << "--->" << std::setprecision(10) << result._ballResults[currentPlayer]._distanceToJack << std::endl;
                testParams2._yaw += 15;
            }
            std::cout << " ********************************************OUIIIIIIIIIIII************************************************ " << std::endl;
           //FIN DU TEST QUI SERT PRESQUE A RIEN
           

           std::cout << " *************************************************TEST**************************************************** " << std::endl;
           //Initialisation pour trouver l'emplacement du cochonnet 
           testParams2._yaw = -180.0;
           
           //4 points : -180, -60, 60, 180
            for(int k=0; k<4; k++){
                Game testGame(game);
                testGame.throwBall(testParams2);
                GameResult result = testGame.computeResult();
                distance.push_back(result._ballResults[currentPlayer]._distanceToJack);
                testParams2._yaw += 120; 
            }

            //trie par borne inf et borne sup
            std::vector<double>::iterator result1 = std::min_element(std::begin(distance), std::end(distance));
            std::cout << "min element at: " << std::distance(std::begin(distance), result1) << std::endl;

            // borne inférieur
            distanceTrier.push_back(distance[std::distance(std::begin(distance), result1)]);
            std::swap(degreeDistance[0],degreeDistance[std::distance(std::begin(distance), result1)]);  
            distance[std::distance(std::begin(distance), result1)]=1000.0;

            //borne supérieur
            result1 = std::min_element(std::begin(distance), std::end(distance));
            std::cout << "min element at: " << std::distance(std::begin(distance), result1) << std::endl;
            distanceTrier.push_back(distance[std::distance(std::begin(distance), result1)]);
            std::swap(degreeDistance[1],degreeDistance[std::distance(std::begin(distance), result1)]);

            //Nettoyage des valeurs inutiles
            degreeDistance.erase(degreeDistance.begin()+3);
            degreeDistance.erase(degreeDistance.begin()+2);

            int k=0;

            //DICHOTOMIE 10 itérations sans amélioration = STOP !!!
            while(k<20){

                //dichotomie
                testParams2._yaw = (degreeDistance[0]+degreeDistance[1] )/2 ;
                trace.push_back(testParams2._yaw);
                Game testGame(game);
                testGame.throwBall(testParams2);
                GameResult result = testGame.computeResult();
                distanceTrier.push_back(result._ballResults[currentPlayer]._distanceToJack);

                std::cout << "******----->" << testParams2._yaw << " " << result._ballResults[currentPlayer]._distanceToJack << std::endl;


                //TRIE POUR LES BORNES INF ET SUP
                //borne supérieur
                std::vector<double>::iterator result2 = std::min_element(std::begin(distanceTrier), std::end(distanceTrier));
                degreeDistance.push_back(testParams2._yaw);
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
                if(result._ballResults[currentPlayer]._distanceToJack < best2){
                    best2 = result._ballResults[currentPlayer]._distanceToJack;
                    bestParams2 = testParams2;
                    k=1;
                }
               
                k++;  
               
               
            } //fin dichotomie
        }
     }
    
     std::cout << " ***************************************************************************************************** " << std::endl;
     std::cout << std::setprecision(10) << best2 << " ->>> " << bestParams2 << std::endl;
     std::cout << std::setprecision(10) << best2 << " ->>> " << testParams2 << std::endl;
     std::cout << std::setprecision(10) << best << " ->>> " << bestParams << std::endl;
     
     
    std::cout << " *****************************************TEST ALGOOO************************************************ " << std::endl;
    for(double n : distance){
        std::cout << "->" <<  std::setprecision(10) << n << std::endl;
    }
    std::cout << " ******Trier********** " << std::endl;
    for(double n : distanceTrier){
        std::cout << "->" <<  std::setprecision(10) << n << std::endl;
    }
    std::cout << " *******degreDistance********* " << std::endl;
    for(int n : degreeDistance){
        std::cout << "->" << n << std::endl;
    }
    std::cout << " *******TRACE********* " << std::endl;
    for(double n : trace){
        std::cout << "->" << n << std::endl;
    }
    std::cout << " *************************************FIN TEST ALGOOO************************************************* " << std::endl;
    
    
    
    
    std::cout << " *************************************OPTIMISATION PITCH************************************************ " << std::endl;
    testParams2._yaw = bestParams2._yaw;
    //OPTIMISATION PITCH
    for(double i=-90.0; i<90.0; i+=1.0){
      testParams2._pitch=i;

      Game testGame(game);
      testGame.throwBall(testParams2);
      GameResult result = testGame.computeResult();

      GameBall positionJack = testGame.getJack();
      std::cout << testParams2._pitch << "--->" << std::setprecision(12) << result._ballResults[currentPlayer]._distanceToJack << "  --->   " <<  testParams2 << "  Position boule : " << result._ballResults[currentPlayer]._position << "    Cochonnet : " << positionJack._transform.getOrigin() <<  std::endl;       
    }
    std::cout << " ************************************FIN OPTIMISATION PITCH************************************************ " << std::endl;
    
    
    */
    
    

     
     //Optimisation yaw : x
//     do{
//        
//         testParams._yaw += 5;
//         if(testParams._yaw >= 180){
//              testParams._yaw=0;
//         }
//         for(int i=-180; i<180; i++){
//             testParams._yaw=i;
//         }
//         
//        //Lancer
//        Game testGame(game);
//        testGame.throwBall(testParams);
//        GameResult result = testGame.computeResult();
//        
//        std::cout << "***" << testParams._yaw << "->>" << result._ballResults[currentPlayer]._distanceToJack << std::endl;
        
//        std::cout << "\t# " <<"---------" << bestDistanceToJack << "---------" << std::endl;
//        std::cout << "\t********" << result._ballResults[currentPlayer]._distanceToJack << " --> "  << bestParams._yaw << "--->" << testParams._yaw << "*******"<< std::endl;
//        
//        testParams._yaw = testParams._yaw + 1.0;
//        
        
//        testParams._pitch = testParams._pitch+1.0;
//         testParams._velocity =  testParams._velocity+1.0;
        
        //Meilleur lancé ou non
//        if(result._ballResults[currentPlayer]._distanceToJack < bestDistanceToJack){
//             bestDistanceToJack = result._ballResults[currentPlayer]._distanceToJack;
//             bestParams._yaw =  testParams._yaw;
//             std::cout << "MEILLEUR !" << std::endl;
//        }
//        i++;
//         
//     }while(i<nbIteration);
     
     
//     //Optimisation yaw : x
//    do{
//        
//        //Lancer
//        Game testGame(game);
//        testGame.throwBall(testParams);
//        GameResult result = testGame.computeResult();
//                
//        //premier tour : direction à prendre
//        if(i<1){
//            
//            bestDistanceToJack = result._ballResults[currentPlayer]._distanceToJack;
//            
//            Game testGame(game); 
//            testParams._yaw = bestParams._yaw;
//            testGame.throwBall(testParams);
//            GameResult result = testGame.computeResult();
//            
//            if(result._ballResults[currentPlayer]._distanceToJack < bestDistanceToJack){
//                std::cout << "OKKKKKKK" << std::endl;
//            }else{
//                std::cout << "NONNNNNNN" << std::endl;
//            }
// 
//        }
//        
//          std::cout << "\t# " <<"---------" << bestDistanceToJack << "---------" << std::endl;
//          std::cout << "\t********" << result._ballResults[currentPlayer]._distanceToJack << " --> "  << bestParams._yaw << "--->" << testParams._yaw << "*******"<< std::endl;
//          
//          
//          //Meilleur lancé ou non
//          if(result._ballResults[currentPlayer]._distanceToJack < bestDistanceToJack){
//               bestDistanceToJack = result._ballResults[currentPlayer]._distanceToJack;
//               testParams._yaw += pas;
//               bestParams._yaw=testParams._yaw;
//               i=2;
//               std::cout << "MEILLEUR !"<<std::endl;
//          }else{
//              //testParams._yaw +=  pas;
//              testParams._yaw = testParams._yaw+1;
//              bestParams._yaw = bestParams._yaw+1;
//          }
//          i++;
//    }while(i<nbIteration);
    
    
    
    
    
    
    
//    do{
//        
//        
//        double n = generateNormalDistribution(0.0, 0.2);
//        ThrowParams testParams;
//
//        testParams._pitch = bestParams._pitch + sigma_pitch * n;
//        testParams._yaw = bestParams._yaw + sigma_yaw * n;
//        testParams._velocity = bestParams._velocity + sigma_velocity * n;  
//        
//        std::cout << "\t# " << testParams._pitch << "\t# " << testParams._yaw << "\t# " << testParams._velocity << std::endl;
//
//        Game testGame(game);
//        testGame.throwBall(testParams);
//        GameResult result = testGame.computeResult();
//        
//        if(result._ballResults[currentPlayer]._distanceToJack < bestDistanceToJack){
//            bestDistanceToJack = result._ballResults[currentPlayer]._distanceToJack;
//            bestParams = testParams;
//            std::cout << bestDistanceToJack << std::endl;
//            
//            sigma_pitch = sigma_pitch * exp(1.0/3.0);
//            sigma_yaw = sigma_yaw * exp(1.0/3.0);
//            sigma_velocity = sigma_velocity * exp(1.0/3.0);
//        }else{
//            sigma_pitch = sigma_pitch / (pow(exp(1.0/3.0),0.25));
//            sigma_yaw = sigma_yaw / (pow(exp(1.0/3.0),0.25));
//            sigma_velocity = sigma_velocity / (pow(exp(1.0/3.0),0.25));
//        }
//        
//        std::cout << "----------" << std::endl;
//        std::cout << "--->" << sigma_pitch << " " << sigma_yaw << " " << sigma_velocity << "<---" << std::endl;
//        std::cout << "----------" << std::endl;
//    }while(bestDistanceToJack >= precision);
        
        
    
    
    std::cout << "FINISH STOP !!!!" << std::endl;

    return bestParams;
}