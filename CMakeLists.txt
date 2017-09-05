cmake_minimum_required(VERSION 3.7)
project(PathFind)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp point.h point.cpp AstarEstimater.cpp AstarEstimater.h PathFinder.cpp PathFinder.h Graph.cpp Graph.h consts.h Floyed.cpp Floyed.h)
add_executable(PathFind ${SOURCE_FILES})