// Copyright © 2014 Teytaud & Dehos <{teytaud,dehos}@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _GAMEOBJECT_TEST_HPP_
#define _GAMEOBJECT_TEST_HPP_

#include "GameObject.hpp"
#include <cxxtest/TestSuite.h>

class GameObject_test : public CxxTest::TestSuite 
{
    public:

        void test_gameobject_1
        {
            GameBall ball1 { btTransform(btMatrix3x3(1,2,3,4,5,6,7,8,9)),
                btVector3(10,11,12), 13, 14)};

            btScalar mat[15];
            ball1._transform.getOpenGLMatrix(mat);
            TS_ASSERT_EQUAL(mat, {1,2,3,1,4,5,6,1,7,8,9,1,0,3,0});
            TS_ASSERT_EQUAL(ball1._velocity, btVector3(10,11,12));
            TS_ASSERT_EQUAL(ball1._mass, btScalar(13));
            TS_ASSERT_EQUAL(ball1._radius, btScalar(14));
        }

};

#endif


