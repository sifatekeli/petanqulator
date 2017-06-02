// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Game.hpp"
#include <math.h>  
#include <map>

class Player 
{
    public:
        std::map<std::string, double> _params;
        virtual ~Player() = default;
        virtual VecParam chooseParams(const Game & game) = 0;
};

class PlayerRandom : public Player 
{
    protected:
        Prng _prng;
    public:
        VecParam chooseParams(const Game & game) override;
};

class PlayerBestRandom : public PlayerRandom 
{
    public:
        PlayerBestRandom();
        VecParam chooseParams(const Game & game) override;
};

class PlayerGoodRandom : public PlayerRandom 
{
    protected:
        btScalar _precision;
    public:
        PlayerGoodRandom(btScalar precision);
        virtual VecParam chooseParams(const Game & game) override;
};

class PlayerOnePlusOneStatic : public PlayerRandom
{
    protected:
        Prng _prng;
        int _nb_iteration;
    public:
        PlayerOnePlusOneStatic(int nb_iteration);
        virtual VecParam chooseParams(const Game & game) override;     
    
};

class PlayerOnePlusOneStaticSmart : public PlayerRandom
{
    protected:
        Prng _prng;
        int _nb_iteration;
    public:
        PlayerOnePlusOneStaticSmart(int nb_iteration);
        virtual VecParam chooseParams(const Game & game) override;     
    
};

class PlayerOnePlusOneDynamic : public PlayerRandom
{
    protected:
        Prng _prng;
        btScalar _precision;
        int _compteur;        
    public:
        PlayerOnePlusOneDynamic(btScalar precision, int compteur);
        virtual VecParam chooseParams(const Game & game) override;     
    
};

class PlayerOnePlusOneDynamicSmart : public PlayerRandom
{
    protected:
        Prng _prng;
        btScalar _precision;
        int _compteur;        
    public:
        PlayerOnePlusOneDynamicSmart(btScalar precision, int compteur);
        virtual VecParam chooseParams(const Game & game) override;     
    
};

class PlayerAverageMu : public PlayerRandom
{
    protected:
        Prng _prng;
        btScalar _precision;
        int _lambdaSize;
        int _muSize;
    public:
        PlayerAverageMu(btScalar precision, int lambdaSize);
        virtual VecParam chooseParams(const Game & game) override;     
    
};

class PlayerAverageMuSmart : public PlayerRandom
{
    protected:
        Prng _prng;
        btScalar _precision;
        int _lambdaSize;
        int _muSize;
    public:
        PlayerAverageMuSmart(btScalar precision, int lambdaSize);
        virtual VecParam chooseParams(const Game & game) override;     
    
};

class PlayerDichotomie : public PlayerRandom{
    
    public: 
        virtual VecParam chooseParams(const Game & game) override;   
};

#endif

