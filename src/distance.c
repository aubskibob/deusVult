/* File:  
 *    distance.c
 *
 * Purpose:
 *    Calculate distance of spherical progression of sound waves
 *
 * Input:
 *    none
 * Output:
 *    message from each process
 *
 * Compile:  gcc -g -Wall -fopenmp -o distance distance.c
 * Usage:    ./distance
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void populateSpace(void);

int main(int argc, char *argv[]){

  // pragma omp parallel num_threads(4)
  populateSpace();

  return 0;	
}

void populateSpace(void)
{
  if((space = (double***)malloc(*sizeof(double**)))==NULL)
    {
      perror("Unable to allocate memory");
      exit(1);
    }
  
  if((data=(float**)malloc(height*sizeof(float*)))==NULL)
    {
      perror("allocate_float_map");
      exit(10);
    }
  for(i=0;i<height;i++)
    if((data[i]=(float*)malloc(width*sizeof(float)))==NULL)
      {
	perror("allocate_float_map");
	exit(10);
      }
}
