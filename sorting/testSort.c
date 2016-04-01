/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Testing out my sorting functions. I am skimping on the error checking
 *  so I can focus on the actual problem
 */

#include <stdio.h>
#include <sort.h>
#include <string.h>
#include <time.h>
#include <utilities.h>

#define DEFAULT_INPUT_FILENAME "./input_files/input.txt"
#define DEFAULT_OUTPUT_FILENAME "./output_files/sorted.log"

void sortAndPrint(int unsortedArray[], int numElements,
   void (*fnptr)(int arr[], int n), char *label, FILE *outputFile);

// TODO: clean up output a little bit
// TODO: sanity check the inputs

int main(int argc, char * argv[])
{
  // read arguments - NO ERROR CHECKING!
  char *inputFileName, *outputFileName;
  if(argc==1){
    inputFileName = DEFAULT_INPUT_FILENAME;
    outputFileName = DEFAULT_OUTPUT_FILENAME;
  } else if(argc==2){
    inputFileName = argv[1];
    outputFileName = DEFAULT_OUTPUT_FILENAME;
  } else if(argc==3){
    inputFileName = argv[1];
    outputFileName = argv[2];
  } else {
    printf("Usage: ./testSort [inputFile [outputFile]]\n");
    exit(1);
  }
  printf("Reading from: %s\n", inputFileName);
  printf("Writing to: %s\n", outputFileName);

  // create input file
  FILE *inputFile;
  if(strcmp(inputFileName, "stdin")==0){
    inputFile = stdin;
  } else {
    inputFile = fopen(inputFileName, "r");
  }

  // create array from input file
  int size = countLines(inputFile);
  int unsortedArray[size];
  getIntArray(unsortedArray, size, inputFile);
  int numElements = sizeof(unsortedArray)/sizeof(unsortedArray[0]);
  fclose(inputFile);

  // open (or create) a file to output results to. (the "a" stands for 'append')
  FILE *outputFile;
  if(strcmp(outputFileName, "stdout")==0){
    outputFile = stdout;
  } else {
    outputFile = fopen(outputFileName, "a");
  }
  timeStamp(outputFile);
  fprintf(outputFile, "------------\n");

  // print unsorted array
  fprintf(outputFile, "Unsorted:       \t");
  fprintIntArray(outputFile, unsortedArray, numElements);
  fprintf(outputFile, "\n");

  // sort em! pass in the sorting function and the label used for printing
  sortAndPrint(unsortedArray, numElements, selectionSort, "Selection Sort: \t",
   outputFile);
  sortAndPrint(unsortedArray, numElements, insertionSort, "Insertion Sort: \t",
   outputFile);
  sortAndPrint(unsortedArray, numElements, mergeSort, "Merge Sort:     \t",
   outputFile);
  sortAndPrint(unsortedArray, numElements, quickSort, "Quick Sort:     \t",
   outputFile);

  fprintf(outputFile, "------------\n");
  fclose(outputFile);
}

// run the sorting functino passed in by fnptr, print results
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
  fprintf(outputFile, "Time taken: %d seconds %d milliseconds\n\n",
   msec/1000, msec%1000);

}
