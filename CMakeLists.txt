cmake_minimum_required(VERSION 2.8)

find_package(MPI REQUIRED)
include_directories(${MPI_C_INCLUDE_PATH})

enable_testing()

find_package(Doxygen)
if(${DOXYGEN_FOUND})
  add_custom_target(doxygen COMMAND ${DOXYGEN_EXECUTABLE})
endif(${DOXYGEN_FOUND})

add_subdirectory(src)
