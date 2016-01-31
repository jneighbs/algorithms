/*
 * Author: Jacob Neighbors
 * Date: 1/30/16
 * Desc: Piggybacking a inversion counting algorithm on top of merge sort.
 *  This keeps the running time at O(nlogn). Based on the algorithms class
 *  taught at Stanford: https://www.coursera.org/course/algo
 */

#include <stdio.h>
#include <string.h>
#include "utilities.h"

/*******************************************************************************
  Name: sortAndCountInversions
  Input:  int *arr - an array of ints (possibly with inversions)
          int n - number of elements in arr
  Return: int numInversions - the number of inversions counted.
  Note: This WILL alter the array that is passed in.
*******************************************************************************/

/* wrapper function */
int sortAndCountInversions(int arr[], int n);
int mergeAndCount(int leftArray[], int leftElements, int rightArray[], int rightElements);


int sortAndCountInversions(int arr[], int n)
{
  /* base case - arrays of size 1 can't be inverted */
  if(n <= 1) return 0;
  
  int numInversions = 0;
  /* recursively sort and count the left half of the array */
  numInversions += sortAndCountInversions(arr, n/2);
  /* recursively sort and count the right half of the array */
  numInversions += sortAndCountInversions(arr + n/2, n-n/2);
  /* merge and count the 2 arrays together into 1 sorted array */
  numInversions += mergeAndCount(arr, n/2, arr+n/2, n-n/2);
  return numInversions;
}

// note - this only works if the 2 arrays are contiguous (ie connected to each other)
int mergeAndCount(int leftArray[], int leftElements, int rightArray[], int rightElements)
{
  int tmpOutputArr[leftElements + rightElements];//placeholder for sorted output
  int l = 0; // index into left array
  int r = 0; // index into right array
  int numInversions = 0;
  // sort, merge, and count!
  for(int i = 0; i < leftElements + rightElements;){
    if(leftArray[l] <= rightArray[r]){
      tmpOutputArr[i++] = leftArray[l++];
      // left array is empty, flush right
      if(l==leftElements){
        while(r < rightElements){
          tmpOutputArr[i++] = rightArray[r++];
        }
      }
    } else {
      numInversions += (leftElements - l);
      tmpOutputArr[i++] = rightArray[r++];
      if(r==rightElements){
        while(l < leftElements){
          tmpOutputArr[i++] = leftArray[l++];
        }
      }
    }
  }

  memcpy(leftArray, tmpOutputArr, (leftElements+rightElements) * sizeof(int));
  return numInversions;
}
