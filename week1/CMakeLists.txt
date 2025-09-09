cmake_minimum_required(VERSION 3.16)
project(week1 VERSION 0.1.0 LANGUAGES C CXX)



include_directories(include)
add_executable(week1_cpp src/week1.cpp)

# Set C++17 standard for the target
set_property(TARGET week1_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET week1_cpp PROPERTY CXX_STANDARD_REQUIRED ON)#