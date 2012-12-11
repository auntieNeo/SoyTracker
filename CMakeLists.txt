cmake_minimum_required(VERSION 2.8)

find_package(MPI REQUIRED)
include_directories(${MPI_C_INCLUDE_PATH})

add_executable(tripripper keyspaceMapping.cpp keyspacePoolFactory.cpp linearKeyspace.cpp main.cpp matchingAlgorithm.cpp tripcodeAlgorithm.cpp)
target_link_libraries(mpi_test_a ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})

enable_testing()

# A simple test that searches for short matches using the simple, dependable,
# straight C implementations of the search strategies.
add_test(NAME simple_test COMMAND simple_test.sh ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 32 $<TARGET_FILE:tripripper> --keyspace-mapping=linear --tripcode-algorithm=openssl --matching-algorithm=strcmp)
