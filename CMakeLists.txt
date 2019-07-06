# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (rover)

# set flag
set(CMAKE_CXX_STANDARD 17)

# Add an executable
add_executable(rover main.cpp)