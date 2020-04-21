project("DBUG" C)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -Wall")

include_directories(include)

file(GLOB_RECURSE DBUG_SOURCES "src/*")

add_library(dbug ${DBUG_SOURCES})

add_subdirectory(examples)