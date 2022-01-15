cmake_minimum_required(VERSION 3.21)
project(RaycastingEngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(RaycastingEngine main.cpp)

include_directories(dependencies/raylib/include)

find_library(RAY_LIB raylib dependencies/raylib)
target_link_libraries(RaycastingEngine LINK_PUBLIC ${RAY_LIB})
target_link_libraries(RaycastingEngine LINK_PUBLIC winmm)
