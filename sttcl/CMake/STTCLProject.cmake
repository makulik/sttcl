
if(STTCL_USE_STL)
    add_definitions("-DSTTCL_USE_STL")
endif()

if(NOT "${STTCL_IMPL}" STREQUAL "")
    add_definitions("-DSTTCL_${STTCL_IMPL}_IMPL")
else()
    add_definitions("-DSTTCL_POSIX_IMPL")
endif()

if("${STTCL_IMPL}" STREQUAL "POSIX")
    set(STTCL_LIBTHREADS_DIR "${STTCL_PATH}/PosixThreads")
    set(STTCL_LIBTIME_DIR "${STTCL_PATH}/PosixTime")
    set(STTCL_ADD_LIBS "pthread")
elseif("${STTCL_IMPL}" STREQUAL "BOOST")
    find_package( Boost 1.51.0 REQUIRED COMPONENTS thread date_time system )
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        set(STTCL_LIBTHREADS_DIR "${STTCL_PATH}/BoostThreads")
        set(STTCL_LIBTIME_DIR "${STTCL_PATH}/BoostTime")
        set(STTCL_ADD_LIBS "${Boost_LIBRARIES}")
    endif()    
endif()

include_directories("${STTCL_PATH}/include")
include_directories("${STTCL_LIBTHREADS_DIR}")
include_directories("${STTCL_LIBTIME_DIR}")

file(GLOB STTCL_LIBTHREADS_SRC "${STTCL_LIBTHREADS_DIR}/src/*.cpp")
file(GLOB STTCL_LIBTIME_SRC "${STTCL_LIBTHREADS_DIR}/src/*.cpp")

add_library(sttcl STATIC ${STTCL_LIBTHREADS_SRC} ${STTCL_LIBTIME_SRC})
set_target_properties(sttcl PROPERTIES LINKER_LANGUAGE CXX)
