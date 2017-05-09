# petanqulator [![Build Status](https://travis-ci.org/juliendehos/petanqulator.svg?branch=master)](https://travis-ci.org/juliendehos/petanqulator)

[PETANQue](https://en.wikipedia.org/wiki/P%C3%A9tanque) simULATOR 

## Dependencies

- bullet physics
- gtkmm, gtkglextmm
- opengl, glu
- cxxtest
- gcc >= 4.9
- cmake

## Build 

```
mkdir build
cd build
cmake ..
# cmake -DCMAKE_BUILD_TYPE=Debug ..
# CXXFLAGS="-DLOG" cmake -DCMAKE_BUILD_TYPE=Debug ..
make 
```

## TODO

- improve camera navigation
- discard out-limit balls
- implement a more interesting terrain
- render ball rotation in OpenGL view (+ rolling friction)
- use a single collision shape + multiples collision objects (for balls)

