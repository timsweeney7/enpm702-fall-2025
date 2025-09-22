cmake_minimum_required(VERSION 3.28)
project(assignment_1 VERSION 1.0 LANGUAGES C CXX)

include_directories(include)
add_executable(assignment_1_cpp src/assignment_1.cpp)

# Set C++17 standard for the target
set_property(TARGET assignment_1_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET assignment_1_cpp PROPERTY CXX_STANDARD_REQUIRED ON)

# enable all warnings
add_compile_options(-Wall -Wextra)
