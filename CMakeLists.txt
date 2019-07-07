cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_STANDARD_REQUIRED ON)

project(rover)

############################################################
# Create a library
############################################################

# Generate the static library from the library sources
add_library(rover_library 
    src/Rover.cpp
)

target_include_directories(rover_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(rover_binary 
    src/main.cpp
)

# link the new hello_library target with the hello_binary target
target_link_libraries( rover_binary
    PRIVATE 
        rover_library
)

############################################################
# Unit tests
############################################################

add_subdirectory(3rd_party/google-test)

# enable CTest testing
enable_testing()

# Add a testing executable
add_executable(unit_tests unit_tests.cpp)

target_link_libraries(unit_tests
    rover_library
    GTest::GTest 
    GTest::Main
)

add_test(test_all unit_tests)


