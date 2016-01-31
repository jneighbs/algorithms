/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Header file for several sorting functions.
 */

#ifndef SORT_H_
#define SORT_H_

int * myInsertionSort(int unsortedArray[], int arrayLength);
// note: I return a malloc'd pointer, so you must free it when done
int * myMergeSort(int unsortedArray[], int arrayLength);
int * myBubbleSort(int unsortedArray[], int arrayLength); //TODO: implement
int * mySelectionSort(int unsortedArray[], int arrayLength);
int * myQuickSort(int unsortedArray[], int arrayLength); //TODO: implement

#endif //SORT_H_
