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

// prints an array of integers in a nice format to the given file
void fprintIntArray(FILE *fp, int arr[], int numElements);

// prints the time and date out to the given file
void timeStamp(FILE *fp);

// gets next line of file from given file
int getLine(char line[], int lineLength, FILE *fp);

// counts the number of lines in the given file
int countLines(FILE *fp);

// coutns the number of words in a token, delim by " \t\n\r"
int countNumWords(FILE *fp);

// convert file of ints into int[], returns array size
int getIntArray(int intArray[], int length, FILE *fp);

// generic swap function
void swap(void *obj1, void *obj2, size_t size);

#endif
