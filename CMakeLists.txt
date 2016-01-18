cmake_minimum_required( VERSION 3.0 )

project( petanqulator )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14" )

find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-2.4 gtkglextmm-1.2 )
include_directories( ${GTKMM_INCLUDE_DIRS} )
#add_definitions( ${GTKMM_CFLAGS_OTHER} )

find_package( GLU REQUIRED )

find_package( Bullet REQUIRED )
include_directories( ${BULLET_INCLUDE_DIRS} )

file(
    GLOB_RECURSE
    SRCS
    src/*
    )

add_executable( petanqulator ${SRCS} )

target_link_libraries( petanqulator ${GTKMM_LIBRARIES} )
target_link_libraries( petanqulator ${BULLET_LIBRARIES} )

