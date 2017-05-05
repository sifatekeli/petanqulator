// Copyright © 2014 Teytaud & Dehos <{teytaud,dehos}@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#include "Prng.hpp"

#include <iostream>

Prng::Prng() : 
    _engine(std::random_device{}()),  
    _distribution(0, 1) 
{
}

void Prng::setSeed(unsigned seed) 
{
    _engine.seed(seed);
#ifdef LOG
    std::clog << "Prng::setSeed(" << seed << ")" << std::endl;
#endif
}

double Prng::generate() 
{
    return _distribution(_engine);
}

double Prng::generate(double a, double b) 
{
    double x = _distribution(_engine);
    double dx = b - a;
    return x*dx + a;
}
double Prng::generateNormalDistribution(double mu, double sigma){
    std::normal_distribution<double> normal(mu, sigma);

    return normal(_engine);
}

double Prng::generateNormalDistribution(double mu, double sigma){
    std::normal_distribution<double> normal(mu, sigma);

    return normal(_engine);
}