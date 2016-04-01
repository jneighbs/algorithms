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
  Name: insertionSort
  Args: unsorted array of ints, num elements in array
*******************************************************************************/
void insertionSort(int unsortedArray[], int arrayLength)
{
  // iterate through unsorted array
  for(int *i = unsortedArray; i < unsortedArray+arrayLength; i++){
    // iterate back through sorted section of array
    for(int *curPosition = i; curPosition > unsortedArray; curPosition--){
      // if previous number greater than cur number
      if(*(curPosition-1) > *curPosition){
          // switch them
          int tmp = *curPosition;
          *curPosition = *(curPosition-1);
          *(curPosition-1) = tmp;
      }
    }
  }
}


/*******************************************************************************
  Name: selectionSort
  Args: an unsorted array of ints, num elements in array
*******************************************************************************/
void selectionSort(int unsortedArray[], int arrayLength)
{
  // iterate through unsorted array
  for(int i = 0; i < arrayLength; i++){
    // search for the min element of array
    int min = unsortedArray[i];
    int minIndex = i;
    for(int j = i+1; j < arrayLength; j++){
      if(unsortedArray[j] < min){
        min = unsortedArray[j];
        minIndex = j;
      }
    }
    // swap min element with element at beginning
    int tmp = unsortedArray[i];
    unsortedArray[i] = min;
    unsortedArray[minIndex] = tmp;
  }
}


/*******************************************************************************
  Name: mergeSort
  Args: an unsorted array of ints, and the number of elements in it
*******************************************************************************/

// the recursive mergeSort function
void mergeSort(int arrayToSort[], int numElements);
// the merge function
void merge(int *l_array, int l_arraySize, int *r_array, int r_arraySize);


void mergeSort(int arrayToSort[], int numElements)
{
  /* Base case! Only sort arrays with more than 1 element! */
  if(numElements > 1){

    /* Separate out left/right half of array, and recursively sort them */
    mergeSort(arrayToSort, numElements/2);
    mergeSort(arrayToSort+numElements/2, numElements-numElements/2);

    /* merge the 2 sorted halves */
    merge(arrayToSort, numElements/2, arrayToSort+numElements/2,
       numElements-numElements/2);
  }
}


// merge the left and right arrays together, in sorted order
void merge(int l_array[], int l_arraySize, int r_array[], int r_arraySize)
{
  // create tmp stack storage to hold the merged array
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
}


/*******************************************************************************
  Name: quickSort
  Args: an unsorted array of ints, and the number of elements in the array
*******************************************************************************/

// wrapper function to conform arguments to other sorting function args
void quickSort(int unsortedArray[], int arrayLength);
// the actual quickSort sorting function
void quickSortRecursive(int unsortedArray[], int beginIndex, int endIndex);
// partitioning fn
int partition(int unsortedArray[], int beginIndex, int endIndex);

// wrapper function to conform arguments to other sorting function args
void quickSort(int unsortedArray[], int arrayLength)
{
  quickSortRecursive(unsortedArray, 0, arrayLength-1);
}

// the actual quickSort sorting function
void quickSortRecursive(int unsortedArray[], int beginIndex, int endIndex)
{
  if(endIndex - beginIndex > 1){
    // (randomly) select a partition, and then partition the array
    int partitionIndex = partition(unsortedArray, beginIndex, endIndex);
    // recursively sort elements to the left/right of the partition
    quickSortRecursive(unsortedArray, beginIndex, partitionIndex-1);
    quickSortRecursive(unsortedArray, partitionIndex+1, endIndex);
  }
}

// grabs partition, moves numbers smaller to the left of it, larger to the right
int partition(int unsortedArray[], int beginIndex, int endIndex)
{
  // TODO: select random number between beginIndex and endIndex to find partition
  int partition = unsortedArray[endIndex];

  // loop through array, values smaller than partition on left, larger on right
  int i = beginIndex-1;
  for(int j=beginIndex; j<endIndex; j++){
    if(unsortedArray[j] < partition){
      int tmp = unsortedArray[++i];
      unsortedArray[i] = unsortedArray[j];
      unsortedArray[j] = tmp;
    }
  }

  unsortedArray[endIndex] = unsortedArray[i+1];
  unsortedArray[i+1] = partition;

  return i+1;
}
