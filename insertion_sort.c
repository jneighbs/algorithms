/*
 * Author: Jacob Neighbors
 * Date: 1/26/16
 * Desc: Insertion sort! Mainly for fun.
 * Input: Array of unsorted numbers
 * Ouptut: Array of sorted numbers
 */

#include <stdio.h>
#define ARRAY_LENGTH 10

int * insertionSort(int unsortedArray[])
{
  int arrayLength = ARRAY_LENGTH;
  // pointers to hold my position
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

int main(int argc, char *argv[])
{
  // gather the input
  // TODO: Make this a separate function. Gather it from a file or from user
  int input[ARRAY_LENGTH] = {2,7,3,1,4,9,0,6,5,8};

  // sorting algorithm
  int *output = insertionSort(input);

  // print the output
  // TODO: Shold probably make this a separate utility function too.
  for(int i = 0; i < ARRAY_LENGTH; i++){
    printf("%d ", *(output+i));
  }
  printf("\n");
}
