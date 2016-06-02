/*
 * Author: Jacob Neighbors
 * Date: 5/26/16
 * Desc: Header file for basic graph structure/functions
 */

#include <stdio.h>

// Vertex Struct
typedef struct {
  int label;                      // vertex label
  struct ConnectorElement *head;  // head of linked list of adjacent edges
  struct ConnectorElement *tail;  // tail of linked list of adjacent edges
} Vertex;

// Edge Struct
typedef struct Edge {
  struct ConnectorElement *endpoint1;  // points to the connector that points to it
  struct ConnectorElement *endpoint2;  // points to the connector that points to it
} Edge;

// ConnectorElement Struct - middleman between edges & vertices. Vertices will
// create a linked list of these to keep track of their adjacent edges.
typedef struct ConnectorElement{
  Edge *adjacentEdge;             // an adjacent edge of the source vertex
  Vertex *sourceVertex;           // the source vertex
  struct ConnectorElement *prev;  // the prev connector element in linked list
  struct ConnectorElement *next;  // the next connector element in linked list
} ConnectorElement;

// Graph struct
typedef struct {
  int numVertices;              // total num vertices in graph
  int numEdges;                 // total num edges in graph
  Vertex *vertices;             // address of array of vertices
  Edge *edges;                  // address of array of edges
  ConnectorElement *connectors; // address of array of ConnectorElements
} Graph;

Graph* createGraph(FILE *fp);
void freeGraph(Graph *g);
Graph* copyGraph(Graph *g);
void printGraph(Graph *g);
void removeEdge(Graph *g, Edge *e);
void removeVertex(Graph *g, Vertex *vp);
int kargerMinCut(FILE *inputFile, int numIterations);
