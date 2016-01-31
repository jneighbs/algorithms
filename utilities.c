/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Decided to write up a few utility functions for my algorithms practice.
 */

#include "utilities.h"
#include <stdio.h>

// malloc that does some error checking automatically
void* myMalloc(size_t size)
{
  void *ptr = malloc(size);
  if(ptr == NULL){
    fprintf(stderr, "ERROR: (fn myMalloc in utilities.c) unable to allocate new space");
    exit(1);
  }
  return ptr;
}

// prints an array of integers in a nice format
// TODO: optional label argument, prettier format
void printIntArray(int arr[], int numElements)
{
  printf("[");
  for(int i = 0; i < numElements; i++){
    i+1 <numElements ? printf(" %d |", arr[i]) : printf(" %d ", arr[i]);

  }
  printf("]\n");
}
