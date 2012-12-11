enable_testing()

# A simple test that searches for short matches using the simple, dependable,
# straight C implementations of the search strategies.
add_test(NAME simple_test COMMAND ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 32 $<TARGET_FILE:tripripper> --keyspace-mapping=linear --tripcode-algorithm=openssl --matching-algorithm=strcmp)
