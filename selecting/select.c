/*
 * Author: Jacob Neighbors
 * Date: 4/6/16
 * Desc: Functions that solve the selection problem (ie - ith order statistics,
 *  the linear time selection problem)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <select.h>
#include <utilities.h>

/*******************************************************************************
  Name: rSelect
  Desc: find and return the ith smallest element in the arrayLength sized array
*******************************************************************************/
int rSelect(int *array, int arrayLength, int i);
int rSelectRecurse(int *array, int i, int startIndex, int endIndex);
int partition(int *array, int startIndex, int endIndex);

int rSelect(int *array, int arrayLength, int i)
{
  // check for proper value of i
  if(i > arrayLength || i < 1) {
    fprintf(stderr, "ERROR: invalid \'i\' value in fn \'rSelect\' in \'select.c\'\n");
    exit(1);
  }

  // recurse and return
  return rSelectRecurse(array, i, 0, arrayLength-1);
}

int rSelectRecurse(int *array, int i, int startIndex, int endIndex)
{
  // base case: if array of size 1, then whats left must be the answer
  if(startIndex>=endIndex){
    if(startIndex>endIndex){
      printf("WEIRD: \n");
      printIntArray(array + startIndex, endIndex - startIndex + 1);
      printf("i: %d, startIndex: %d, endIndex: %d\n", i, startIndex, endIndex);
    }
    return array[startIndex];
  }

  // partition array around pivot
  int pivotIndex = partition(array, startIndex, endIndex);
  int pivotOrder = pivotIndex+1; // increment bc 0th index is 1st order, etc

  // if we are lucky enough to have guessed the right index, return it
  if(i == pivotOrder) return array[pivotIndex];

  // if i < pivot, return everything left of pivot (ie all smaller)
  if(i < pivotOrder){
    return rSelectRecurse(array, i, startIndex, pivotIndex-1);

  // else return everything right of pivot, adjust i accordingly
  } else {
    return rSelectRecurse(array, i, pivotIndex+1, endIndex);
  }
}

int partition(int *array, int startIndex, int endIndex)
{
  // select random pivot
  time_t t;
  srand((unsigned) &t);
  int range = endIndex-startIndex+1;
  int pivotIndex = startIndex+rand()%range;
  int pivot = array[pivotIndex];

  // swap pivot and last element
  int tmp = array[endIndex];
  array[endIndex] = array[pivotIndex];
  array[pivotIndex] = tmp;

  // printf("pivot: %d\n", pivot);


  // loop through array, values smaller than pivot on left, larger on right
  int i = startIndex-1;
  for(int j=startIndex; j<endIndex; j++){
    if(array[j] < pivot){
      // swap
      int tmp = array[++i];
      array[i] = array[j];
      array[j] = tmp;
    }
  }

  pivotIndex = i+1;
  array[endIndex] = array[pivotIndex];
  array[pivotIndex] = pivot;

  // printIntArray(array+startIndex, endIndex-startIndex+1);


  return pivotIndex;
}
