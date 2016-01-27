#include <stdio.h>
#include "sort.h"
#define INPUT {99,7,1042,-93,4,5,6,12,0,54,6,88,42}

int main(){
  int unsortedArray[] = INPUT;
  int numElements = sizeof(unsortedArray)/sizeof(unsortedArray[0]);
  // print unsorted array
  for(int i = 0; i < numElements; i++){
    printf("%d ", unsortedArray[i]);
  }
  printf("\n");

  // int *sorted = myInsertionSort(unsortedArray, numElements);
  int *sorted = mySelectionSort(unsortedArray, numElements);

  for(int i = 0; i < numElements; i++){
    printf("%d ", *(sorted+i));
  }
  printf("\n");
}
