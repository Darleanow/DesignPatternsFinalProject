cmake_minimum_required(VERSION 3.10)
project(Design_Patterns)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Design_Patterns ${SOURCES})