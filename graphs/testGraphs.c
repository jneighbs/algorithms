#include <graph.h>
#include <mincut.h>

int main(int argc, char *argv[])
{
  // create graph
  // TODO - read in graph from file
  int numVertices = 4;
  int numEdges = 4;
  Vertex vertices[numVertices];
  Edge edges[numEdges];
  Graph g = {numVertices, numEdges, vertices, edges};
}
