/*
 * Author: Jacob Neighbors
 * Date: 1/26/16
 * Desc: Several sorrting functions! Mainly for fun.
 */

#include <stdio.h>
#include <string.h>
#include "sort.h"

//
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
