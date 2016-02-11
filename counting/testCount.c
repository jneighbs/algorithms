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


int main(int argc, char *argv[])
{
  int count = countLines(stdin);
  int input[count];
  getIntArray(input, count, stdin);

  // printf("Input Array:\t");
  // printIntArray(input, sizeof(input)/sizeof(int));
  printf("Num inversions:\t%d\n", sortAndCountInversions(input, sizeof(input)/sizeof(int)));
  // printf("Output Array:\t");
  // printIntArray(input, sizeof(input)/sizeof(int));
  // TODO: print output aray to a file
  return 0;
}
