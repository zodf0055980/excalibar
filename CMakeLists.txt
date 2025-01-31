cmake_minimum_required(VERSION 3.9)
project(excalibar VERSION 1.0.5)

# CMake scripts in ./cmake
# 1. BuildType.cmake - determine build type on demand
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(BuildType)

# Request C++14 standard, using new CMake variables.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -Wall")

# If the BuildType is Debug, then add -rdynamic.
# (used to print stacktrace with function names)
if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -rdynamic")
endif()


# Find the required libraries.
find_package(X11 REQUIRED)

# CMake will generate config.h from config.h.in
if(APPLE)
  include_directories("src" "/opt/X11/include")
  link_directories("/opt/X11/lib")
else()
  include_directories("src")
endif()

# configure_file("src/config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/config.h")

# Grab all files end in .cc
FILE(GLOB_RECURSE cpp_sources src/*.cc)
add_executable(excalibar ${cpp_sources})

set(LINK_LIBRARIES X11)
target_link_libraries(excalibar ${LINK_LIBRARIES})

# Install rule
install(TARGETS excalibar DESTINATION bin)
