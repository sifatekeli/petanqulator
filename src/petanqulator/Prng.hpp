// Copyright © 2014 Teytaud & Dehos <{teytaud,dehos}@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _PRNG_HPP_
#define _PRNG_HPP_

#include <random>

// Pseudo-random number generator. 
class Prng
{
    private:
        std::mt19937 _engine;
        std::uniform_real_distribution<double> _distribution;
    public:
        Prng();
        void setSeed(unsigned seed);
        // generate a random number in [0, 1)
        double generate();
        // generate a random number in [a, b)
        double generate(double a, double b);
};

#endif

