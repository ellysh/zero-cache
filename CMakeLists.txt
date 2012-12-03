# Release build type:
# cmake -D CMAKE_BUILD_TYPE=Release CMakeLists.txt
#
# Debug build type (by default):
# cmake -D CMAKE_BUILD_TYPE=Debug CMakeLists.txt
# or
# cmake CMakeLists.txt

cmake_minimum_required(VERSION 2.6)
project(zero-cache)

if(UNIX)
  find_package(ZMQ REQUIRED)
  find_package(CZMQ REQUIRED)
  include_directories( ${Boost_INCLUDE_DIR} )
endif(UNIX)

if(UNIX)
  set(CMAKE_INSTALL_PREFIX /usr)
endif(UNIX)

set(COMMON_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/source/client
    ${PROJECT_SOURCE_DIR}/source/common
    ${PROJECT_SOURCE_DIR}/source/server)

set(COMMON_LIBDIR
    ${PROJECT_SOURCE_DIR}/source/client
    ${PROJECT_SOURCE_DIR}/source/common
    ${PROJECT_SOURCE_DIR}/source/server)

# Build type by default is Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

message(STATUS "Build type: " ${CMAKE_BUILD_TYPE})

# CXXFLAGS and CMAKE_C_FLAGS
if(UNIX)
  set(CMAKE_CXX_FLAGS "-Wvla -Wl,-z,defs -fPIC")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -fomit-frame-pointer -funroll-loops -pipe")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -O0")
  set(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
endif(UNIX)

# Subdirs
add_subdirectory(source)
add_subdirectory(test)
#add_subdirectory(conf)

include(CMakeListsDeb.txt)
