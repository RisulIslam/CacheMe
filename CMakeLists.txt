cmake_minimum_required(VERSION 3.0)
project(CacheSim)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Simulation.cpp Simulation.h Predictor.cpp Predictor.h Cache.cpp Cache.h)
add_executable(CacheSim ${SOURCE_FILES})