/*
 * Author: Jacob Neighbors
 * Date: 1/27/16
 * Desc: Header file for several sorting functions.
 */

#ifndef SORT_H_
#define SORT_H_

void insertionSort(int unsortedArray[], int arrayLength);
void mergeSort(int unsortedArray[], int arrayLength);
//void bubbleSort(int unsortedArray[], int arrayLength); TODO: implement
void selectionSort(int unsortedArray[], int arrayLength);
void quickSort(int unsortedArray[], int arrayLength);

#endif //SORT_H_
