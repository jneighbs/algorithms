#include <stdio.h>
#include <utilities.h>

#define MAXLINE 100

int main(int argc, char *argv[]){
  // char line[MAXLINE];
  // int count = 0;
  // while((getLine(line, MAXLINE)) > 0){
  //   count++;
  // }

  int count = countLines(stdin);
  printf("Count: %d\n", count);

  int arr[count];
  int size = getIntArray(arr, count, stdin);
  printIntArray(arr, size);
}
