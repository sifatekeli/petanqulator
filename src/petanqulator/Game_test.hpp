// Copyright © 2014 Teytaud & Dehos <{teytaud,dehos}@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _GAME_TEST_HPP_
#define _GAME_TEST_HPP_

#include "Game.hpp"
#include <cxxtest/TestSuite.h>

class Game_test : public CxxTest::TestSuite 
{
    public:

        void test_game_1
        {
            Game game1;
            game1.newTurn();
            GameBall jack1 = game1.getJack();
            Game game2(game1);
            GameBall jack2 = game2.getJack();
            TS_ASSERT(jack1==jack2);
            TS_ASSERT(jack1.getPosition()==jack2.getPosition());
        }

};

#endif

