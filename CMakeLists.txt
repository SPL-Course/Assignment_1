cmake_minimum_required(VERSION 3.17)
project(Assignment_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Assignment_1
        #bin/main.o
        #bin/Tree.o
        #include/Agent.h
        #include/config1.json
        #include/config4.json
        #include/Graph.h
        #include/json.hpp
        #include/Session.h
        #include/Tree.h
        src/Agent.cpp
        src/Graph.cpp
        src/main.cpp
        src/Session.cpp
        src/Tree.cpp)
        #CMakeLists.txt
        #makefile)
