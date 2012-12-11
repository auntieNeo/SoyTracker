#include <cunistd>

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  MPI_Finalize();
  return EXIT_SUCCESS;
}
