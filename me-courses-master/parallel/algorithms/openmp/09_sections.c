#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Run a task for the given section.
 */
void run_section(char name)
{
  int thread_id;

  thread_id = omp_get_thread_num();
  printf("[%d] Section %c\n", thread_id, name);
}

/**
 * Sections
 */
int main(int argc, char* argv[])
{
  #pragma omp parallel
  {
    #pragma omp sections
    {
      #pragma omp section
      run_section('A');
      #pragma omp section
      run_section('B');
      #pragma omp section
      run_section('C');
      #pragma omp section
      run_section('D');
      #pragma omp section
      run_section('E');
      #pragma omp section
      run_section('F');
    }
  }

  return 0;
}
