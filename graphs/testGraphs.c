#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graph.h>
#include <utilities.h>


void readCommandLineArguments(int argc, char *argv[], FILE **inputFile);
#define NUM_ITERATIONS 2000

int main(int argc, char *argv[])
{
  FILE *inputFile;
  readCommandLineArguments(argc, argv, &inputFile);
  clock_t start = clock();
  int minCut = kargerMinCut(inputFile, NUM_ITERATIONS);
  clock_t diff = clock() - start;

  // print errthing
  int msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("minCut: %d\n", minCut);
  printf("numIterations: %d\n", NUM_ITERATIONS);
  printf("CPU ticks: %ld\n", diff);
  printf("Time taken: %d seconds %d milliseconds\n", msec/1000, msec%1000);
}

void readCommandLineArguments(int argc, char **argv, FILE **inputFile)
{
  char instructions[] = "usage: ./testGraphs filename";
  if(argc != 2){
    printf("%s\n", instructions);
    exit(1);
  }
  *inputFile = fopen(argv[1], "r");
  if(inputFile==NULL){
    printf("File %s failed to open.\n%s\n", argv[1], instructions);
    exit(1);
  }
}
