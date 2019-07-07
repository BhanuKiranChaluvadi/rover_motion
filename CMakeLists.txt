# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

# set flag
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_STANDARD_REQUIRED ON)

# Set the project name
project(rover)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/Rover.cpp
    src/main.cpp
)

# Add an executable with the above sources
add_executable(rover_headers ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(rover_headers
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

#############################################



