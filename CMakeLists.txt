cmake_minimum_required(VERSION 3.8)
project(capitalone)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES CodeLineCounter.cpp)
add_executable(capitalone ${SOURCE_FILES})