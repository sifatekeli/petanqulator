cmake_minimum_required( VERSION 3.0 )

project( petanqulator )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set( CMAKE_CXX_STANDARD 14 )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter" )
endif()

find_package( PkgConfig REQUIRED )

# petanqulator library
find_package( Bullet REQUIRED )
include_directories( ${BULLET_INCLUDE_DIRS} )
pkg_check_modules( EIGEN REQUIRED eigen3 )
include_directories( ${EIGEN_INCLUDE_DIRS} )
file( GLOB PETANQULATOR_SOURCE src/petanqulator/*pp )
INCLUDE_DIRECTORIES( src )
ADD_LIBRARY ( petanqulator STATIC ${PETANQULATOR_SOURCE} )
target_link_libraries( petanqulator ${BULLET_LIBRARIES} ) 

# test executable
add_executable( petanqulator_test1.out src/petanqulator_test/petanqulator_test1.cpp )
target_link_libraries( petanqulator_test1.out petanqulator )
add_executable( petanqulator_test2.out src/petanqulator_test/petanqulator_test2.cpp )
target_link_libraries( petanqulator_test2.out petanqulator )
add_executable( petanqulator_test3.out src/petanqulator_test/petanqulator_test3.cpp )
target_link_libraries( petanqulator_test3.out petanqulator )
add_executable( petanqulator_test_analyse.out src/petanqulator_test/petanqulator_test_analyse.cpp )
target_link_libraries( petanqulator_test_analyse.out petanqulator )

# cli executable
add_executable( petanqulator_cli.out src/petanqulator_cli/petanqulator_cli.cpp )
target_link_libraries( petanqulator_cli.out petanqulator )

# gui executable
pkg_check_modules( GTKMM REQUIRED gtkmm-2.4 gl gtkglextmm-1.2 )
include_directories( ${GTKMM_INCLUDE_DIRS} )
find_package( GLU REQUIRED )
file( GLOB GUI_SOURCE src/petanqulator_gui/*pp )
add_executable( petanqulator_gui.out ${GUI_SOURCE} )
target_link_libraries( petanqulator_gui.out petanqulator ${GTKMM_LIBRARIES} )

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

