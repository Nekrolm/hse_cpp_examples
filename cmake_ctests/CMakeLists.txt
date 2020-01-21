cmake_minimum_required(VERSION 3.15)

project(Test)

include(CTest)
find_package(GTest CONFIG REQUIRED)

add_subdirectory(src)