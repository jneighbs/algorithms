/*
 * Author: Jacob Neighbors
 * Date: 1/26/16
 * Desc: Insertion sort! Mainly for fun.
 * Input: Array of unsorted numbers
 * Ouptut: Array of sorted numbers
 */

#include <stdio.h>

int * insertionSort(int unsortedArray[])
{
  return NULL;
}

int main(int argc, char *argv[])
{
  // gather the input
  // TODO: Make this a separate function. Gather it from a file or from user
  int input[10] = {2,7,3,1,4,9,0,6,5,8};

  // sorting algorithm
  int *output = insertionSort(input);

  // print the output
  // TODO: Shold probably make this a separate function too.
  for(int i = 0; i < 10; i++){
    printf("%d ", *(output+i));
  }
  printf("\n");
}
