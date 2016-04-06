/*
 * Author: Jacob Neighbors
 * Date: 4/6/16
 * Desc: Functions that solve the selection problem (ie - ith order statistics,
 *  the linear time selection problem)
 */

#ifndef SELECT_H_
#define SELECT_H_

//linear time selection using a randomized pivot
int rSelect(int *array, int arrayLength, int i);

#endif
