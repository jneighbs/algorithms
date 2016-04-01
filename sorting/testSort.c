/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Testing out my sorting functions. I am skimping on the error checking
 *  so I can focus on the meat of the problem
 */

#include <stdio.h>
#include <sort.h>
#include <string.h>
#include <time.h>
#include <utilities.h>

#define DEFAULT_OUTPUT_FILENAME "./output_files/sorted.log"
#define DEFAULT_INPUT_FILENAME "./input_files/input.txt"

void sortAndPrint(int unsortedArray[], int numElements,
   void (*fnptr)(int arr[], int n), char *label, FILE *outputFile);

// TODO: time each sorting operation, print time to output file
// TODO: usage: ./testSort inputFile outputFile
// TODO: sanity check the inputs

int main(int argc, char * argv[])
{
  // create array from redirected elements from stdin
  int size = countLines(stdin);
  int unsortedArray[size];
  getIntArray(unsortedArray, size, stdin);
  int numElements = sizeof(unsortedArray)/sizeof(unsortedArray[0]);

  // open (or create) a file to output results to. (the "a" stands for 'append')
  FILE *outputFile = fopen(DEFAULT_OUTPUT_FILENAME, "a");
  timeStamp(outputFile);

  // print unsorted array
  fprintf(outputFile, "Unsorted: \t\t\t");
  fprintIntArray(outputFile, unsortedArray, numElements);

  // sort em! pass in the sorting function and the label used for printing
  sortAndPrint(unsortedArray, numElements, selectionSort, "Selection Sort: ",
   outputFile);
  sortAndPrint(unsortedArray, numElements, insertionSort, "Insertion Sort: ",
   outputFile);
  sortAndPrint(unsortedArray, numElements, mergeSort, "Merge Sort: \t\t",
   outputFile);
  sortAndPrint(unsortedArray, numElements, quickSort, "Quick Sort: \t\t",
   outputFile);
  fprintf(outputFile, "\n");
}


void sortAndPrint(int unsortedArray[], int numElements,
   void (*fnptr)(int arr[], int n), char *label, FILE *outputFile)
{
  // copy unsorted array over to new array
  int arrayToSort[numElements];
  memcpy(arrayToSort, unsortedArray, numElements * sizeof(int));

  clock_t start = clock();
  (*fnptr)(arrayToSort, numElements); //call fn pointed at by fnptr
  clock_t diff = clock() - start;

  // print errthing
  fprintf(outputFile, "%s", label);
  fprintIntArray(outputFile, arrayToSort, numElements);
  int msec = diff * 1000 / CLOCKS_PER_SEC;
  fprintf(outputFile, "CPU ticks: %ld\n", diff);
  fprintf(outputFile, "Time taken: %d seconds %d milliseconds\n",
   msec/1000, msec%1000);

}
