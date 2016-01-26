/*
 * Author: Jacob Neighbors
 * Date: 1/26/16
 * Desc: Insertion sort! Mainly for fun.
 * Input: Array of unsorted numbers
 * Ouptut: Array of sorted numbers
 */

#include <stdio.h>

int * insertionSort(int unsortedArray[])
{
  int arrayLength = 11;
  int *begin = unsortedArray;
  int *end = begin + arrayLength;

  for(int *i = begin; i < end; i++){
    int curNum = *i;
    for(int *curPosition = i; curPosition > begin; curPosition--){
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

int main(int argc, char *argv[])
{
  // gather the input
  // TODO: Make this a separate function. Gather it from a file or from user
  int input[11] = {2,7,3,1,4,9,0,6,5,8, 10};

  // sorting algorithm
  int *output = insertionSort(input);

  // print the output
  // TODO: Shold probably make this a separate function too.
  for(int i = 0; i < 11; i++){
    printf("%d ", *(output+i));
  }
  printf("\n");
}
