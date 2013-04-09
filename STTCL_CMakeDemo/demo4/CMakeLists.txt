cmake_minimum_required(VERSION 2.8)

project(demo4)

# Adjust the following options for your build and target environment
option(STTCL_USE_STL "Use STL for STTCL implementations" ON)

# You need to choose from a standard STTCL implementation or provide a custom implementation
# for certain STTCL features. The available standard implementations are:
# * BOOST Use STTCL's internal boost based implementation
# * POSIX Use STTCL's internal POSIX based implementation
# * CX11 Use STTCL's internal C++11 standard based implementation
# * CUSTOM Use a custom implementation for STTCL thread, timing and synchronization implementations 
set(STTCL_IMPL "BOOST")
# Adjust your STTCL source path
set(STTCL_PATH "c:/Users/Admin/sttcl/sttcl")

# If BOOST implementation is selected you'll need to specify your Boost installation path.
# POSIX or CX11 implementations should be found in the standard path's of your toolchain.
# TODO: Implement a mechanism to integrate STTCL custom OS implementations. 
set(BOOST_ROOT "c:/MinGw/msys/1.0/opt/boost_1_51_0")

# Include the STTCL cmake project settings 
# This will initiate compilation of the concrete sttcl implementation library and
# set the STTCL_ADD_LIBS variable to link the libraries the implementation depends on.
include(${STTCL_PATH}/CMake/STTCLProject.cmake)

# Add all the source to build the target application
file(GLOB appSrc "${PROJECT_SOURCE_DIR}/src/*.cpp") 
add_executable(demo4 ${appSrc})

# Add all libraries and dependent libraries necessary to build the application 
target_link_libraries(demo4 sttcl ${STTCL_ADD_LIBS})
