/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Testing out my sorting functions.
 */

#include <stdio.h>
#include <sort.h>
#include <utilities.h>
#define FILENAME "./output_files/sorted.log"
// #define INPUT_STUB {8,10,3,9,4,2,5,1,7,6,500,100,4,0,123,17,44,103,42,42,42}

// TODO: time each sorting operation, print time to output file
// TODO: usage: ./testSort inputFile outputFile
int main(int argc, char * argv[]){

  // create array from elements in stdin
  int size = countLines(stdin);
  int unsortedArray[size];
  getIntArray(unsortedArray, size, stdin);
  int numElements = sizeof(unsortedArray)/sizeof(unsortedArray[0]);

  // open (or create) a file to output results to. (the 'a' stands for 'append')
  FILE *outputFile = fopen(FILENAME, "a");
  timeStamp(outputFile);

  /* unsorted array */
  fprintf(outputFile, "Unsorted: \t\t\t");
  fprintIntArray(outputFile, unsortedArray, numElements);

  /* insertion sort */
  int *sorted1 = myInsertionSort(unsortedArray, numElements);
  fprintf(outputFile, "Insertion Sort: ");
  fprintIntArray(outputFile, sorted1, numElements);
  free(sorted1);

  /* selection sort */
  int *sorted2 = mySelectionSort(unsortedArray, numElements);
  fprintf(outputFile, "Selection Sort: ");
  fprintIntArray(outputFile, sorted2, numElements);
  free(sorted2);

  /* merge sort */
  int *sorted3 = myMergeSort(unsortedArray, numElements);
  fprintf(outputFile, "Merge Sort: \t\t");
  fprintIntArray(outputFile, sorted3, numElements);
  free(sorted3);

  /* quick sort */
  int *sorted4 = (int *)malloc(sizeof(int) * numElements);
  memcpy(sorted4, unsortedArray, sizeof(int) * numElements);
  myQuickSort(sorted4, numElements);
  fprintf(outputFile, "Quick Sort: \t\t");
  fprintIntArray(outputFile, sorted4, numElements);
  free(sorted4);

  fprintf(outputFile, "\n");
}
