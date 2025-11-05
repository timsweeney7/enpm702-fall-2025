cmake_minimum_required(VERSION 3.28)
project(week8 VERSION 1.0 LANGUAGES C CXX)

add_executable(week8_cpp src/main.cpp src/vehicle.cpp)
add_executable(snippets_cpp src/snippets.cpp)

target_include_directories(week8_cpp PRIVATE include)

# Set C++17 standard for the targets
set_property(TARGET week8_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET week8_cpp PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET snippets_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET snippets_cpp PROPERTY CXX_STANDARD_REQUIRED ON)

