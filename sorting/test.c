#include <stdio.h>
#include "sort.h"
#define INPUT {99,7,1042,-93,4,5,6,12,0,54,6,88,42}

int main(){
  int unsortedArray[] = INPUT;
  int numElements = sizeof(unsortedArray)/sizeof(unsortedArray[0]);

  // print unsorted array
  printf("Unsorted: \t\t");
  for(int i = 0; i < numElements; i++){
    printf("%d ", unsortedArray[i]);
  }
  printf("\n");

  // int *sorted = myInsertionSort(unsortedArray, numElements);
  // int *sorted = mySelectionSort(unsortedArray, numElements);
  int *sorted3 = myMergeSort(unsortedArray, numElements);

  printf("myMergeSort: \t\t");
  for(int i = 0; i < numElements; i++){
    printf("%d ", *(sorted3+i));
  }
  printf("\n");

  printf("Unsorted again: \t");
  for(int i = 0; i < numElements; i++){
    printf("%d ", unsortedArray[i]);
  }
  printf("\n");
}
