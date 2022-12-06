cmake_minimum_required(VERSION 3.20)
project(LR_1_algorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(LR_1_algorithm main.cpp src/grammar.h src/analyser.h src/situation.h src/condition.h
        src/grammar.cpp src/analyser.cpp src/situation.cpp src/condition.cpp)
