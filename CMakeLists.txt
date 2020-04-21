project("DBUG" C)
cmake_minimum_required(VERSION 3.0)

include_directories(include)

file(GLOB_RECURSE DBUG_SOURCES "src/*")

add_library(dbug ${DBUG_SOURCES})

add_subdirectory(examples)