#
# Options Générales
#
cmake_minimum_required(VERSION 2.6)

project(othello)

set(PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(PROJECT_BINARY_DIR "build/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -g3")
set(CMAKE_CXX_STANDART 11)

#
# Compilation des sources
#
file(GLOB srcs src/*)

add_executable(run ${srcs})

# Ajout de la target docs
find_package(Doxygen)
option(DOCUMENTATION "Crée et installe une API de documentation basée sur HTML (Doxygen)" ${DOXYGEN_FOUND})

if (DOCUMENTATION)
	if (NOT DOXYGEN_FOUND)
		message(FATAL_ERROR "Doxygen est obligatoire pour créer la documentation.")
	endif()
	
	set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
	
	configure_file(${doxyfile_in} ${doxyfile} @ONLY)
	
	add_custom_target(docs
		COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Génération de la documentation (Doxygen)"
		VERBATIM
	)
	
#	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif()
