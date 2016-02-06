// Copyright © 2015 Dehos <dehos@lisic.univ-littoral.fr>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See the COPYING.WTFPL file for more details.

#ifndef _GAMEOBJECT_TEST_HPP_
#define _GAMEOBJECT_TEST_HPP_

#include <petanqulator/GameObject.hpp>
#include <cxxtest/TestSuite.h>

class GameObject_test : public CxxTest::TestSuite 
{
    public:

        void test_gameobject_1()
        {
            GameBall ball1 { btTransform(btMatrix3x3(1,2,3,4,5,6,7,8,9)),
                btVector3(10,11,12), 13, 14};
            btScalar result_mat[15];
            ball1._transform.getOpenGLMatrix(result_mat);
            btScalar expected_mat[15] {1,4,7,0,2,5,8,0,3,6,9,0,0,0,0};
            for (int i=0; i<15; i++)
                TS_ASSERT_EQUALS(result_mat[i], expected_mat[i]);
            TS_ASSERT_EQUALS(ball1._velocity, btVector3(10,11,12));
            TS_ASSERT_EQUALS(ball1._mass, btScalar(13));
            TS_ASSERT_EQUALS(ball1._radius, btScalar(14));
        }

};

#endif


