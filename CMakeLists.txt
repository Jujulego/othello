#
# Options Générales
#
cmake_minimum_required(VERSION 2.6)

project(othello)

set(PROJECT_BINARY_DIR "build/cmake")

#
# Compilation des sources
#
file(GLOB srcs src/*)

add_executable(run ${srcs})

