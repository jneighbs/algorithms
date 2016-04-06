/*
 * Author: Jacob Neighbors
 * Date: 4/6/16
 * Desc: Testing out my selection functions
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <select.h>
#include <utilities.h>
#define FILENAME_BUFFER 32

void readInput(int argc, char *argv[], int *i, FILE **inputFile, FILE **outputFile);

int main(int argc, char *argv[])
{
  // read in args, check valid input, print out usage messages
  int i;
  FILE *inputFile = stdin;
  FILE *outputFile = stdout;
  readInput(argc, argv, &i, &inputFile, &outputFile);

  // create array from input file
  int size = countLines(inputFile);
  int array[size];
  getIntArray(array, size, inputFile);
  int arrayLength = sizeof(array)/sizeof(array[0]);
  fclose(inputFile);

  // find ith order statistic and print to output file
  fprintf(outputFile, "%d\n", rSelect(array, arrayLength, i));
}


// reads in the input arguments from the command line, sanity checks them,
// assigns them to variables, and prints error messages
void readInput(int argc, char *argv[], int *i, FILE **inputFile, FILE **outputFile)
{
  char *usageInstructions = "Usage: ./testSelect i [-i inputFilename][-o outputFilename]\n";

  // need to make sure the user provides the 'i'
  if(argc < 2){
    printf("%s", usageInstructions);
    return;
  }

  for(int j = 1; j < argc; j++){

    //grab i, the ith order statistic (ith smallest number)
    if(j==1){
      *i = atoi(argv[j]);
      if(*i==0){
        printf("\"i\" must be a number.\n%s", usageInstructions);
        return;
      }
    // search for -i option (sets the input file)
    } else if(strcmp(argv[j], "-i")==0){
      if(++j >= argc) {
        printf("No filename detected after \"-i\".\n%s", usageInstructions);
        return;
      }
      *inputFile = fopen(argv[j], "r");
      if(*inputFile == NULL){
        printf("Unable to open file \"%s\"\n%s", argv[j], usageInstructions);
        return;
      }

    // search for -o option (sets the output file)
    } else if(strcmp(argv[j], "-o")==0){
      if(++j >= argc) {
        printf("No filename detected after \"-o\".\n%s", usageInstructions);
        return;
      }
      *outputFile = fopen(argv[j], "w");
    }

  }
}
