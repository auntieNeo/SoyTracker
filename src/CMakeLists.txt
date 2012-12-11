add_executable(tripripper keyspaceMapping.cpp keyspacePoolFactory.cpp linearKeyspace.cpp main.cpp matchingAlgorithm.cpp tripcodeAlgorithm.cpp)
target_link_libraries(mpi_test_a ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})

add_subdirectory(tests)
