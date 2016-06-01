#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <utilities.h>


void readCommandLineArguments(int argc, char *argv[], FILE **inputFile);


int main(int argc, char *argv[])
{
  FILE *inputFile;
  readCommandLineArguments(argc, argv, &inputFile);
  Graph *g = createGraph(inputFile);
  printGraph(g);
  // TODO: delete edge here
  printGraph(g);

}

void readCommandLineArguments(int argc, char **argv, FILE **inputFile)
{
  char instructions[] = "usage: ./testGraphs filename";
  if(argc != 2){
    printf("%s\n", instructions);
    exit(1);
  }
  *inputFile = fopen(argv[1], "r");
  if(inputFile==NULL){
    printf("File %s failed to open.\n%s\n", argv[1], instructions);
    exit(1);
  }
}
