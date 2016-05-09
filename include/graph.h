/*
 * Author: Jacob Neighbors
 * Date: 5/9/16
 * Desc: Header file for basic graph structure/functions
 */


typedef struct {
  struct Edge *adjacentEdges;  // linked list of Edge pointers
} Vertex;

typedef struct Edge {
  Vertex *u;            // one endpoint of the edge
  Vertex *v;            // other endpoint of the edge
} Edge;

typedef struct {
  int numVertices;      // total num vertices in graph
  int numEdges;         // total num edges in graph
  Vertex *vertices;     // address of array of vertices
  Edge *edges;          // address of array of edges
} Graph;
