cmake_minimum_required(VERSION 3.20)
project(LR_1_algorithm)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS --coverage)

add_executable(LR_1_algorithm main.cpp src/solution.h src/grammar.h src/analyser.h src/situation.h src/condition.h
        src/solution.cpp src/grammar.cpp src/analyser.cpp src/situation.cpp src/condition.cpp)

#include(FetchContent)
#
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG release-1.12.1
#)
#
#FetchContent_MakeAvailable(googletest)
#
#enable_testing()
#
#add_executable(test1 tests/test1.cpp src/solution.h src/grammar.h src/analyser.h src/situation.h src/condition.h
#        src/solution.cpp src/grammar.cpp src/analyser.cpp src/situation.cpp src/condition.cpp)
#
#target_link_libraries(
#        test1
#        GTest::gtest_main
#)
#
#include(GoogleTest)
#gtest_discover_tests(test1)

