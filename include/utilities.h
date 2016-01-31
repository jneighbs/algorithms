/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Header file for my utility functions
 */

#ifndef MY_UTILITIES_H_
#define MY_UTILITIES_H_
#include <stdlib.h>

// malloc wrapper that does some error checking automatically
void* myMalloc(size_t size);

// prints an array of integers in a nice format
void printIntArray(int arr[], int numElements);

#endif
