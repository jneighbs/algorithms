/*
 * Author: Jacob Neighbors
 * Date: 1/31/16
 * Desc: Testing out my counting algorithms
 */

#include <stdio.h>
#include <count.h>
#include <utilities.h>
#define INPUT {1,2,3,4,5,6,7,8,10,9}
#define MAXLINE 100
#define MAXARRAYLEN 1000000
#define FILENAME "./output_files/counted.txt"


int main(int argc, char *argv[])
{
  // read/create int array from file
  int count = countLines(stdin);
  int input[count];
  getIntArray(input, count, stdin);

  // open file and timestamp
  FILE *outputFile = fopen(FILENAME, "a");
  timeStamp(outputFile);

  // print input array
  fprintf(outputFile, "Input Array:\t");
  fprintIntArray(outputFile, input, sizeof(input)/sizeof(int));

  // sort file and count inversions
  unsigned long numInversions = sortAndCountInversions(input, sizeof(input)/sizeof(int));
  fprintf(outputFile, "Output Array:\t");
  fprintIntArray(outputFile, input, sizeof(input)/sizeof(int));
  fprintf(outputFile, "Num inversions:\t%lu\n\n", numInversions);
  return 0;
}
