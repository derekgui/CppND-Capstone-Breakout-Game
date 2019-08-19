cmake_minimum_required(VERSION 3.7)

if(NOT TESTING)
    set(TESTING "notest")
endif()

message("TESTING = ${TESTING}")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(SDL2Breakout)

#
# Project Output
#
set(MAINFOLDER ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${MAINFOLDER}/bin")
set(LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

#
# Locate dependencies 
#
find_package(SDL2 REQUIRED)

#
#Add sub-build tree
#
if(${TESTING} STREQUAL "notest")
    add_subdirectory(src)
else()
    add_subdirectory(src)
    add_subdirectory(test)
    add_subdirectory(googletest)
endif()