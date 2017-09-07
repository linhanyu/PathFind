cmake_minimum_required(VERSION 3.7)
project(PathFind)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp consts.h Floyed.cpp Floyed.h)
add_executable(PathFind ${SOURCE_FILES})