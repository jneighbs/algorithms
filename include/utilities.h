/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Header file for my utility functions
 */

#ifndef MY_UTILITIES_H_
#define MY_UTILITIES_H_
#include <stdlib.h>
#include <stdio.h>

// malloc wrapper that does some error checking automatically
void* myMalloc(size_t size);

// prints an array of integers in a nice format
void printIntArray(int arr[], int numElements);

// gets next line of file from stdin
int getLine(char line[], int lineLength, FILE *fp);

// counts the number of lines in the file stdin
int countLines(FILE *fp);

// convert file of ints into int[], returns array size
int getIntArray(int intArray[], int length, FILE *fp);

#endif
