cmake_minimum_required(VERSION 3.28)
project(assignment_3 VERSION 1.0 LANGUAGES C CXX)

include_directories(include)
add_executable(assignment_3_cpp 
    src/main.cpp
    src/robot_types.cpp
    src/robot_control.cpp
)

# Set C++17 standard for the target
set_property(TARGET assignment_3_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET assignment_3_cpp PROPERTY CXX_STANDARD_REQUIRED ON)

# enable all warnings
add_compile_options(-Wall -Wextra -pedantic-errors)


# --- Add this section to integrate Valgrind ---
# Find the valgrind executable on the system
find_program(VALGRIND_EXECUTABLE valgrind)

# Only create the targets if valgrind is found
if(VALGRIND_EXECUTABLE)

    # --- Target for Memory Leak Checking (memcheck) ---
    add_custom_target(memcheck)

    add_custom_command(
        TARGET memcheck
        COMMAND ${VALGRIND_EXECUTABLE} --leak-check=full --track-origins=yes $<TARGET_FILE:assignment_3_cpp>
        COMMENT "Running Valgrind Memcheck on assignment_3_cpp"
    )

    # Ensure executables are built before any tool runs
    # add_dependencies(memcheck week3_cpp week3_exercise)
    add_dependencies(memcheck assignment_3_cpp)

endif()