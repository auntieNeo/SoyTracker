#add_executable(tripripper keyspaceMapping.cpp keyspacePoolFactory.cpp linearKeyspace.cpp main.cpp matchingAlgorithm.cpp tripcodeAlgorithm.cpp)
add_executable(tripripper main.cpp)
target_link_libraries(tripripper ${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})

add_subdirectory(tests)
