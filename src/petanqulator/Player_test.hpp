// Copyright © 2014 Teytaud & Dehos <{teytaud,dehos}@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _PLAYER_TEST_HPP_
#define _PLAYER_TEST_HPP_

#include "Player.hpp"
#include <cxxtest/TestSuite.h>

class Player_test : public CxxTest::TestSuite 
{
    public:

        void test_player_1 () 
        {
            const int nbSamples = 1e6;
            double sum = 0.0;
            Prng prng;
            for (int i=0; i<nbSamples; i++) 
            {
                double s = prng.generate(40.0, 44.0);
                sum += s;
                TS_ASSERT(s >= 40.0);
                TS_ASSERT(s < 44.0);
            }
            double mean = sum / (double)nbSamples;
            TS_ASSERT_DELTA(mean, 42.0, 0.1);
        }

};

#endif


