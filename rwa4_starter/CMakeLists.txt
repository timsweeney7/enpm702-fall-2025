cmake_minimum_required(VERSION 3.28)
project(rwa4 VERSION 1.0 LANGUAGES C CXX)

add_executable(rwa4_cpp src/main.cpp src/maze_api.cpp)

target_include_directories(rwa4_cpp PRIVATE include)

# Set C++17 standard for the targets
set_property(TARGET rwa4_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET rwa4_cpp PROPERTY CXX_STANDARD_REQUIRED ON)