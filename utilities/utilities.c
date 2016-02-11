/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Decided to write up a few utility functions for algorithm practice.
 */

#include <utilities.h>
#include <stdio.h>
#include <stdlib.h>

// malloc that does some error checking automatically
void* myMalloc(size_t size)
{
  void *ptr = malloc(size);
  if(ptr == NULL){
    fprintf(stderr, "ERROR: (fn myMalloc in utilities.c) unable to allocate new space");
    exit(1);
  }
  return ptr;
}

// prints an array of integers in a nice format
// TODO: optional label argument, prettier format
void printIntArray(int arr[], int numElements)
{
  printf("[");
  for(int i = 0; i < numElements; i++){
    i+1 <numElements ? printf("%6d|", arr[i]) : printf("%6d", arr[i]);

  }
  printf("]\n");
}

// gets next line of file
int getLine(char line[], int lineLength, FILE *fp)
{
  int i = 0;
  int c;

  while(i<lineLength-1 && (c=getc(fp)) != EOF){
    line[i++]=c;
    if(c=='\n') break;
  }
  line[i] = '\0';
  return i;
}

// counts the number of lines in given file
int countLines(FILE *fp)
{
  int count = 0;
  int maxLen = 1000;
  char line[maxLen];

  while(getLine(line, maxLen, fp) > 0) count++;
  rewind(fp);
  return count;
}

// converts file into an int array. File must be formatted such that each line
// of the file is a single integer to be input into the array
int getIntArray(int intArray[], int length, FILE *fp)
{
  int maxNumDigits = 12;
  char line[maxNumDigits+1];
  int i = 0;
  while(getLine(line, maxNumDigits+1, fp) > 0){
    if(i>=length){
      fprintf(stderr, "ERROR (Fn: getIntArray) - File too big! Increase the \'length\' parameter to fix.\n");
    }
    intArray[i++] = atoi(line);
  }
  return i;
}
