A very thin, mostly 2D wrapper for glut and simple
geometric structures.

To compile CMake must be installed.
freeglut can be used for GLUT implementation (on ubuntu: apt-get install freeglut3-dev)

To build:

```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/installprefix ..
make install
```

This will compile and install to ```installprefix``` directory. 

The geom package can be used without compiling
as it is a pure template library.

