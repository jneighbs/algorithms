/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Testing out my sorting functions.
 */

#include <stdio.h>
#include <sort.h>
#include <utilities.h>
#define INPUT {8,10,3,9,4,2,5,1,7,6,500,100,4,0,123,17,44,103,42,42,42}

int main(){
  int unsortedArray[] = INPUT;
  int numElements = sizeof(unsortedArray)/sizeof(unsortedArray[0]);

  /* unsorted array */
  printf("Unsorted: \t");
  printIntArray(unsortedArray, numElements);

  /* insertion sort */
  // int *sorted1 = myInsertionSort(unsortedArray, numElements);
  // printf("myInsertionSort: \t\t");
  // printIntArray(sorted1, numElements);

  /* selection sort */
  // int *sorted2 = mySelectionSort(unsortedArray, numElements);
  // printf("mySelectionSort: \t\t");
  // printIntArray(sorted2, numElements);

  /* merge sort */
  int *sorted3 = myMergeSort(unsortedArray, numElements);
  printf("myMergeSort: \t");
  printIntArray(sorted3, numElements);

  // printf("Unsorted again: ");
  // printIntArray(unsortedArray, numElements);
}