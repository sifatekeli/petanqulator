/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_Player_test_init = false;
#include "/home/kevin/Bureau/master/projet/petanqulator/src/unittest/Player_test.hpp"

static Player_test suite_Player_test;

static CxxTest::List Tests_Player_test = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Player_test( "/home/kevin/Bureau/master/projet/petanqulator/src/unittest/Player_test.hpp", 12, "Player_test", suite_Player_test, Tests_Player_test );

static class TestDescription_suite_Player_test_test_player_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Player_test_test_player_1() : CxxTest::RealTestDescription( Tests_Player_test, suiteDescription_Player_test, 16, "test_player_1" ) {}
 void runTest() { suite_Player_test.test_player_1(); }
} testDescription_suite_Player_test_test_player_1;

#include "/home/kevin/Bureau/master/projet/petanqulator/src/unittest/GameObject_test.hpp"

static GameObject_test suite_GameObject_test;

static CxxTest::List Tests_GameObject_test = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_GameObject_test( "/home/kevin/Bureau/master/projet/petanqulator/src/unittest/GameObject_test.hpp", 12, "GameObject_test", suite_GameObject_test, Tests_GameObject_test );

static class TestDescription_suite_GameObject_test_test_gameobject_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_GameObject_test_test_gameobject_1() : CxxTest::RealTestDescription( Tests_GameObject_test, suiteDescription_GameObject_test, 16, "test_gameobject_1" ) {}
 void runTest() { suite_GameObject_test.test_gameobject_1(); }
} testDescription_suite_GameObject_test_test_gameobject_1;

#include "/home/kevin/Bureau/master/projet/petanqulator/src/unittest/Prng_test.hpp"

static Prng_test suite_Prng_test;

static CxxTest::List Tests_Prng_test = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Prng_test( "/home/kevin/Bureau/master/projet/petanqulator/src/unittest/Prng_test.hpp", 12, "Prng_test", suite_Prng_test, Tests_Prng_test );

static class TestDescription_suite_Prng_test_test_prng_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Prng_test_test_prng_1() : CxxTest::RealTestDescription( Tests_Prng_test, suiteDescription_Prng_test, 16, "test_prng_1" ) {}
 void runTest() { suite_Prng_test.test_prng_1(); }
} testDescription_suite_Prng_test_test_prng_1;

static class TestDescription_suite_Prng_test_test_prng_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Prng_test_test_prng_2() : CxxTest::RealTestDescription( Tests_Prng_test, suiteDescription_Prng_test, 33, "test_prng_2" ) {}
 void runTest() { suite_Prng_test.test_prng_2(); }
} testDescription_suite_Prng_test_test_prng_2;

static class TestDescription_suite_Prng_test_test_prng_3 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Prng_test_test_prng_3() : CxxTest::RealTestDescription( Tests_Prng_test, suiteDescription_Prng_test, 49, "test_prng_3" ) {}
 void runTest() { suite_Prng_test.test_prng_3(); }
} testDescription_suite_Prng_test_test_prng_3;

#include "/home/kevin/Bureau/master/projet/petanqulator/src/unittest/Game_test.hpp"

static Game_test suite_Game_test;

static CxxTest::List Tests_Game_test = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Game_test( "/home/kevin/Bureau/master/projet/petanqulator/src/unittest/Game_test.hpp", 12, "Game_test", suite_Game_test, Tests_Game_test );

static class TestDescription_suite_Game_test_test_game_1 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Game_test_test_game_1() : CxxTest::RealTestDescription( Tests_Game_test, suiteDescription_Game_test, 16, "test_game_1" ) {}
 void runTest() { suite_Game_test.test_game_1(); }
} testDescription_suite_Game_test_test_game_1;

static class TestDescription_suite_Game_test_test_game_2 : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Game_test_test_game_2() : CxxTest::RealTestDescription( Tests_Game_test, suiteDescription_Game_test, 29, "test_game_2" ) {}
 void runTest() { suite_Game_test.test_game_2(); }
} testDescription_suite_Game_test_test_game_2;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
