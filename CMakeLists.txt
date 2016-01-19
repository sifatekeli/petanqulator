cmake_minimum_required( VERSION 3.0 )
project( petanqulator )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra" )
file( GLOB_RECURSE SRCS src/* )
add_executable( petanqulator ${SRCS} )
# gtkmm
find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-2.4 gtkglextmm-1.2 )
include_directories( ${GTKMM_INCLUDE_DIRS} )
target_link_libraries( petanqulator ${GTKMM_LIBRARIES} )
# glu
find_package( GLU REQUIRED )
# bullet
find_package( Bullet REQUIRED )
include_directories( ${BULLET_INCLUDE_DIRS} )
target_link_libraries( petanqulator ${BULLET_LIBRARIES} )

