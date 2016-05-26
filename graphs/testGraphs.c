#include <stdio.h>
#include <graph.h>

void readCommandLineArguments(int argc, char *argv[], FILE **inputFile);


int main(int argc, char *argv[])
{
  FILE *inputFile;
  readCommandLineArguments(argc, argv, &inputFile);
  Graph *g = createGraph(inputFile);
}

void readCommandLineArguments(int argc, char *argv[], FILE **inputFile)
{
  // char instructions[] = "Usage instructions: \'%s inputFilename\'", argv[0];
}
