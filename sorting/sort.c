/*
 * Author: Jacob Neighbors
 * Date: 1/26/16
 * Desc: Several sorrting functions! Mainly for fun.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "../utilities.h"

// insertion sort!
// TODO: don't modify the array that is passed in
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
// TODO: don't modify the array that is passed in
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

/*******************************************************************************
  Name: mergeSort!
  Args: A pointer to an unsorted array of ints, and n, the number of elements
  Return: A malloc'd pointer to a new sorted array
*******************************************************************************/

// wrapper for mergeSortRecursive
int * myMergeSort(int *unsortedArray, int numElements);
// the recursive mergeSort function
int * mergeSortRecursive(int *arrayToSort, int numElements);
// the merge function
int * merge(int *l_array, int l_arraySize, int *r_array, int r_arraySize);



int * myMergeSort(int *unsortedArray, int numElements)
{
  // create new array in heap, check for errors
  int *arrayToSort = (int*) myMalloc(numElements*sizeof(int));

  // copy input array onto our newly allocated array
  memcpy(arrayToSort, unsortedArray, numElements * sizeof(int));

  // return our new, sorted array
  return mergeSortRecursive(arrayToSort, numElements);
}

int * mergeSortRecursive(int *arrayToSort, int numElements)
{
  /* Base case! If only 1 element, then it must be sorted! */
  if(numElements <= 1) return arrayToSort;

  /* Separate out left half of array and recursively sort it */
  int *l_array = arrayToSort;
  int l_arraySize = numElements/2;
  l_array = mergeSortRecursive(l_array, l_arraySize);

  /* Separate out right half of array and recursively sort it */
  int *r_array = arrayToSort + l_arraySize;
  int r_arraySize = numElements - l_arraySize;
  r_array = mergeSortRecursive(r_array, r_arraySize);

  /* return the merged versions */
  return merge(l_array, l_arraySize, r_array, r_arraySize);
}

// merge the left and right arrays together, in sorted order
int * merge(int *l_array, int l_arraySize, int *r_array, int r_arraySize)
{
  int totalSize = l_arraySize + r_arraySize;
  // malloc and error check
  int *tmpArray = (int *) myMalloc(totalSize * sizeof(int));

  int i = 0;  //l_array index
  int j = 0;  //r_array index
  int k = 0;  //tmpArray index

  // copy both halves over to tmpArray in sorted order
  while(k<totalSize){
    if(*(l_array+i) < *(r_array+j)){
      *(tmpArray+k++) = *(l_array+i++);
      // This array is empty. Flush the other array
      if(i==l_arraySize){
        while(j<r_arraySize) *(tmpArray+k++) = *(r_array+j++);
        break;
      }
    } else {
      *(tmpArray+k++) = *(r_array+j++);
      // This array is empty. Flush the other array
      if(j==r_arraySize){
        while(i<l_arraySize) *(tmpArray+k++) = *(l_array+i++);
        break;
      }
    }
  }

  // copy tmp array back over the array that was passed in
  memcpy(l_array, tmpArray, totalSize*sizeof(int));
  free(tmpArray);
  return l_array;
}
