cmake_minimum_required(VERSION 3.17)
project(Assignment_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Assignment_1
        src/Agent.cpp
        src/Graph.cpp
        src/main.cpp
        src/Session.cpp
        src/Tree.cpp)
