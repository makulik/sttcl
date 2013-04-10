This demo illustrates how to setup a CMake based build environment integrating STTCL into the
application.
STTCL provides a CMake include (see sttcl/CMake/STTCLProject.cmake) that will care about all
necessary 3rd party library dependencies.

You can just configure your toolchain (e.g. using CMake-GUI) specifying demo4 as source directory
and generate the build system into a build directory of your choice.