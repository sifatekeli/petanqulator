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

VecParam Prng::generate(const VecParam & pmin, const VecParam & pmax) 
{
    double pitch = generate(pmin(0), pmax(0));
    double yaw = generate(pmin(1), pmax(1));
    double velocity = generate(pmin(2), pmax(2));
    return VecParam(pitch, yaw, velocity);
}

