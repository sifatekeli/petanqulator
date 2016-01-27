# petanqulator
PETANQue simULATOR

https://en.wikipedia.org/wiki/P%C3%A9tanque

### Build ###
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=RELEASE ..
make 
```

## TODO
- improve camera navigation
- discard out-limit balls
- implement a more interesting terrain
- render ball rotation in OpenGL view (+ rolling friction)
- use a single collision shape + multiples collision objects (for balls)

