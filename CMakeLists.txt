cmake_minimum_required(VERSION 3.31.6)
project(nodePointerPractice)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(nodePointerPractice
        core.h
        fireworkNode.cpp
        particle.cpp
        particle.h)
