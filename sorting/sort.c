/*
 * Author: Jacob Neighbors
 * Date: 1/26/16
 * Desc: Several sorrting functions! Mainly for fun.
 */

#include <stdio.h>
#include <string.h>
#include "sort.h"

// insertion sort!
int * myInsertionSort(int unsortedArray[], int arrayLength)
{
  int *begin = unsortedArray;
  int *end = begin + arrayLength;

  // iterate through unsorted array
  for(int *i = begin; i < end; i++){
    // iterate back through sorted section of array
    for(int *curPosition = i; curPosition > begin; curPosition--){
      // if previous number greater than cur number
      if(*(curPosition-1) > *curPosition){
          // switch them
          int tmp = *curPosition;
          *curPosition = *(curPosition-1);
          *(curPosition-1) = tmp;
      }
    }
  }
  return unsortedArray;
}

// selection sort!
int * mySelectionSort(int unsortedArray[], int arrayLength)
{
  int begin = 0;
  int end = begin + arrayLength;

  // iterate through unsorted array
  for(; begin < end; begin++){
    // search for the min element of array
    int min = unsortedArray[begin];
    int minIndex = begin;
    for(int i = minIndex+1; i < end; i++){
      if(unsortedArray[i] < min){
        min = unsortedArray[i];
        minIndex = i;
      }
    }
    // swap min element with element at beginning
    int tmp = unsortedArray[begin];
    unsortedArray[begin] = min;
    unsortedArray[minIndex] = tmp;
  }
  return unsortedArray;
}
