cmake_minimum_required( VERSION 3.0 )
project( petanqulator )
#set(CMAKE_CXX_STANDARD 14)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra" )
if( NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Release )
endif()

# petanqulator library
file( GLOB PETANQULATOR_SOURCE src/petanqulator/*pp )
INCLUDE_DIRECTORIES( src )
ADD_LIBRARY ( petanqulator STATIC ${PETANQULATOR_SOURCE} )
# bullet
find_package( Bullet REQUIRED )
include_directories( ${BULLET_INCLUDE_DIRS} )
target_link_libraries( petanqulator ${BULLET_LIBRARIES} ) 

# test executable
file( GLOB TEST_SOURCE src/petanqulator_test/*pp )
add_executable( petanqulator_test.out ${TEST_SOURCE} )
target_link_libraries( petanqulator_test.out petanqulator )

# cli executable
file( GLOB CLI_SOURCE src/petanqulator_cli/*pp )
add_executable( petanqulator_cli.out ${CLI_SOURCE} )
target_link_libraries( petanqulator_cli.out petanqulator )

# gui executable
file( GLOB GUI_SOURCE src/petanqulator_gui/*pp )
add_executable( petanqulator_gui.out ${GUI_SOURCE} )
target_link_libraries( petanqulator_gui.out petanqulator )
# gtkmm
find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-2.4 gl gtkglextmm-1.2 )
include_directories( ${GTKMM_INCLUDE_DIRS} )
target_link_libraries( petanqulator_gui.out ${GTKMM_LIBRARIES} )
# glu
find_package( GLU REQUIRED )

# unit test
find_package( CxxTest )
if( CXXTEST_FOUND )
    file( GLOB UNITTEST_SOURCE src/unittest/*pp )
    include_directories( ${CXXTEST_INCLUDE_DIRS} )
    enable_testing()
    CXXTEST_ADD_TEST( unittest.out unittest.cpp ${UNITTEST_SOURCE} )
    target_link_libraries( unittest.out petanqulator )
endif()

install (TARGETS petanqulator_cli.out petanqulator_gui.out DESTINATION bin)

