// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _GAME_TEST_HPP_
#define _GAME_TEST_HPP_

#include <petanqulator/Game.hpp>
#include <cxxtest/TestSuite.h>

class Game_test : public CxxTest::TestSuite 
{
    public:

        void test_game_1()
        {
            Game game1;
            game1.newGame();
            GameBall jack1 = game1.getJack();
            Game game2(game1);
            GameBall jack2 = game2.getJack();
            TS_ASSERT(jack1._transform == jack2._transform);
            TS_ASSERT(jack1._velocity == jack2._velocity);
            TS_ASSERT(jack1._mass == jack2._mass);
            TS_ASSERT(jack1._radius == jack2._radius);
        }

        void test_game_2()
        {
            Game game1;
            game1.newGame();
            GameBall jack1 = game1.getJack();
            Game game2(game1);
            game1.newGame();
            GameBall jack1p = game1.getJack();
            GameBall jack2 = game2.getJack();
            // assert jack1 == jack2
            TS_ASSERT(jack1._transform == jack2._transform);
            TS_ASSERT(jack1._velocity == jack2._velocity);
            TS_ASSERT(jack1._mass == jack2._mass);
            TS_ASSERT(jack1._radius == jack2._radius);
            // assert jack1p != jack2
            TS_ASSERT(not (jack1p._transform == jack2._transform));
            TS_ASSERT(jack1p._velocity == jack2._velocity);
            TS_ASSERT(jack1p._mass == jack2._mass);
            TS_ASSERT(jack1p._radius == jack2._radius);
        }

};

#endif

