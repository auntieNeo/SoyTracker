cmake_minimum_required(VERSION 2.8)

find_package(MPI REQUIRED)
include_directories(${MPI_C_INCLUDE_PATH})

enable_testing()

add_subdirectory(src)
