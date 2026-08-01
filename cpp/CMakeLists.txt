cmake_minimum_required(VERSION 3.20)
project(gilded-rose-refactoring-kata-cpp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

string(REPLACE "--coverage" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# uncomment this line to enable coverage measurements using gcov
set(CMAKE_CXX_FLAGS "--coverage")

option(BUILD_APPROVAL_TESTS_WITH_GTEST "Use GoogleTest for approval testing" OFF)
option(BUILD_UNIT_TESTS_WITH_GTEST "Use GoogleTest for unit testing" OFF)
option(BUILD_APPROVAL_TESTS_WITH_CATCH2 "Use Catch2 for approval testing" OFF)
option(BUILD_UNIT_TESTS_WITH_CATCH2 "Use Catch2 for unit testing" ON)

enable_testing()
add_subdirectory(src)
add_subdirectory(test)