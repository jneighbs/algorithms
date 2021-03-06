/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Decided to write up a few utility functions for algorithm practice.
 */

#include <utilities.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// prints an array of integers in a nice format to given file
// TODO: optional label argument, prettier format
void fprintIntArray(FILE *fp, int arr[], int numElements)
{
  fprintf(fp, "[");
  for(int i = 0; i < numElements; i++){
    i+1 <numElements ? fprintf(fp, "%6d|", arr[i]) : fprintf(fp, "%6d", arr[i]);

  }
  fprintf(fp, "]\n");
}

// prints an array of integers in a nice format
void printIntArray(int arr[], int numElements)
{
  fprintIntArray(stdout, arr, numElements);
}

// prints the time and date out to the given file
void timeStamp(FILE *fp)
{
  time_t curTime;
  time(&curTime);
  fprintf(fp, "Timestamp: %s", ctime(&curTime));
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

// counts the number of words in a file
int countNumWords(FILE *fp)
{
  int maxLen = 1000; // maximum length of a line in the file
  char line[maxLen]; // will hold one line of the file at a time
  char delim[] = " \t\r\n\f\v";
  int numWords = 0;
  while(fgets(line, maxLen, fp)){
    if(strtok(line, delim)){
      numWords++;
      while(strtok(NULL, delim)){
        numWords++;
      }
    }
  }
  rewind(fp);
  return numWords;
}

// converts file into an int array. File must be formatted such that each line
// of the file is a single integer to be input into the array
int getIntArray(int intArray[], int length, FILE *fp)
{
  int maxNumDigits = 15;
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

//generic swapping function
void swap(void *obj1, void *obj2, size_t size)
{
  char tmp[size];
  memcpy(tmp, obj1, size);
  memcpy(obj1, obj2, size);
  memcpy(obj2, tmp, size);
}
