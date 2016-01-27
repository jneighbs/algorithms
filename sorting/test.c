#include <stdio.h>
#include "sort.h"
#define INPUT {3, 10, 2, 4, 7, 5, 6, 1, 9, 8, 14, 0, 19, 12, 3}

int main(){
  int unsortedArray[] = INPUT;
  int numElements = sizeof(unsortedArray)/sizeof(unsortedArray[0]);

  int *sorted = myInsertionSort(unsortedArray, numElements);
  for(int i = 0; i < numElements; i++){
    printf("%d ", *(sorted+i));
  }
  printf("\n");
}
