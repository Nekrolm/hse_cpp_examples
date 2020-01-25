cmake_minimum_required(VERSION 3.15)

project(Test)

set(CXX_STANDARD 14)

include(CTest)
find_package(GTest CONFIG REQUIRED)

add_subdirectory(src)
