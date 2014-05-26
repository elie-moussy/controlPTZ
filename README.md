controlPTZ
==========


This software implements the handling and the command of two AXIS cameras PTZ.


Setup
-----

To compile this package, it is recommended to create a separate build
directory:

    mkdir _build
    cd _build
    cmake [OPTIONS] ..
    make install

Please note that CMake produces a `CMakeCache.txt` file which should
be deleted to reconfigure a package from scratch.


### Dependencies

This package depends on several others which
have to be available on your machine.

 - Libraries:
   - opencv (>= 2.4.2)
   - curl
 - System tools:
   - CMake (>=2.6)
   - pkg-config
   - usual compilation tools (GCC/G++, make, etc.)
