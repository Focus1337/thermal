cmake_minimum_required(VERSION 3.23)
project(thermal)

# Add MPI Package to Project
find_package(MPI REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(thermal main.cpp)

# Add libraries for code completion and compiling
target_link_libraries(thermal PUBLIC MPI::MPI_CXX)