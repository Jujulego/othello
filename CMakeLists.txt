#
# Options Générales
#
cmake_minimum_required(VERSION 2.6)

project(othello)

set(PROJECT_BINARY_DIR "build/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -g3")
set(CMAKE_CXX_STANDART 11)

#
# Compilation des sources
#
file(GLOB srcs src/*)

add_executable(run ${srcs})

