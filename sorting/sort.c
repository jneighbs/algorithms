/*
 * Author: Jacob Neighbors
 * Date: 1/26/16
 * Desc: Several sorting functions! Mainly for fun.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sort.h>
#include <utilities.h>


/*******************************************************************************
  Name: myInsertionSort
  Args: A pointer to an unsorted array of ints, num elements in array
  Return: Sorted array! This is a malloc'd version. Have to free it when done.
*******************************************************************************/
int * myInsertionSort(int unsortedArray[], int arrayLength)
{
  int *arrayToSort = (int*) myMalloc(arrayLength * sizeof(int));
  memcpy(arrayToSort, unsortedArray, arrayLength * sizeof(int));

  // iterate through unsorted array
  for(int *i = arrayToSort; i < arrayToSort+arrayLength; i++){
    // iterate back through sorted section of array
    for(int *curPosition = i; curPosition > arrayToSort; curPosition--){
      // if previous number greater than cur number
      if(*(curPosition-1) > *curPosition){
          // switch them
          int tmp = *curPosition;
          *curPosition = *(curPosition-1);
          *(curPosition-1) = tmp;
      }
    }
  }
  return arrayToSort;
}

/*******************************************************************************
  Name: mySelectionSort
  Args: A pointer to an unsorted array of ints, num elements in array
  Return: Malloc'd sorted array
*******************************************************************************/
int * mySelectionSort(int unsortedArray[], int arrayLength)
{
  int *arrayToSort = (int*) myMalloc(arrayLength * sizeof(int));
  memcpy(arrayToSort, unsortedArray, arrayLength * sizeof(int));

  // iterate through unsorted array
  for(int i = 0; i < arrayLength; i++){
    // search for the min element of array
    int min = arrayToSort[i];
    int minIndex = i;
    for(int j = i+1; j < arrayLength; j++){
      if(arrayToSort[j] < min){
        min = arrayToSort[j];
        minIndex = j;
      }
    }
    // swap min element with element at beginning
    int tmp = arrayToSort[i];
    arrayToSort[i] = min;
    arrayToSort[minIndex] = tmp;
  }

  return arrayToSort;
}

/*******************************************************************************
  Name: myMergeSort
  Args: A pointer to an unsorted array of ints, and n, the number of elements
  Return: A malloc'd pointer to a new sorted array
*******************************************************************************/

// wrapper function - allocates some memory for the array so I dont overwrite the original
int * myMergeSort(int arrayToSort[], int numElements);
// the recursive mergeSort function
int * mergeSortRecursive(int *arrayToSort, int numElements);
// the merge function
int * merge(int *l_array, int l_arraySize, int *r_array, int r_arraySize);

int * myMergeSort(int arrayToSort[], int numElements)
{
  int *sortedArray = (int *) myMalloc(numElements * sizeof(int));
  memcpy(sortedArray, arrayToSort, numElements * sizeof(int));
  return mergeSortRecursive(sortedArray, numElements);
}

// the recursive mergeSort function! split the arrays in half, then merge the sorted halves!
int * mergeSortRecursive(int arrayToSort[], int numElements)
{
  /* Base case! If only 1 element, then it must be sorted! */
  if(numElements <= 1) return arrayToSort;

  /* Separate out left/right half of array and recursively sort them */
  mergeSortRecursive(arrayToSort, numElements/2);
  mergeSortRecursive(arrayToSort+numElements/2, numElements-numElements/2);

  /* return the merged versions */
  return merge(arrayToSort, numElements/2, arrayToSort+numElements/2, numElements-numElements/2);
}

// merge the left and right arrays together, in sorted order
int * merge(int l_array[], int l_arraySize, int r_array[], int r_arraySize)
{
  int totalSize = l_arraySize + r_arraySize;
  int outputArray[totalSize];

  int l = 0;  //l_array index
  int r = 0;  //r_array index
  int k = 0;  //outputArray index

  // copy both halves over to outputArray in sorted order
  while(k<totalSize){
    if(l_array[l] < r_array[r]){
      outputArray[k++] = l_array[l++];
      // This array is empty. Flush the other array
      if(l==l_arraySize)
        while(r<r_arraySize) outputArray[k++] = r_array[r++];
    } else {
      outputArray[k++] = r_array[r++];
      // This array is empty. Flush the other array
      if(r==r_arraySize)
        while(l<l_arraySize) outputArray[k++] = l_array[l++];
    }
  }

  // copy outputArray back over the array that was passed in
  memcpy(l_array, outputArray, totalSize*sizeof(int));
  return l_array;
}

/*******************************************************************************
  Name: myQuickSort
  Args: A pointer to an unsorted array of ints, and n, the number of elements
*******************************************************************************/

int partition(int unsortedArray[], int beginIndex, int endIndex)
{
  return 0;
}

void quickSortRecursive(int unsortedArray[], int beginIndex, int endIndex)
{
  if(endIndex-beginIndex > 1){

    // (randomly) select a partition, and then partition the array
    int partitionIndex = partition(unsortedArray, beginIndex, endIndex);

    // recursively sort elements to the left/right of the partition
    quickSortRecursive(unsortedArray, beginIndex, partitionIndex-1);
    quickSortRecursive(unsortedArray, partitionIndex+1, endIndex);
  }
}

void myQuickSort(int unsortedArray[], int arrayLength)
{
  quickSortRecursive(unsortedArray, 0, arrayLength-1);
}
