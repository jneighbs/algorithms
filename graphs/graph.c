/*
 * Author: Jacob Neighbors
 * Date: 5/26/16
 * Desc: Source file for graph functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graph.h>
#include <utilities.h>

Graph* createGraph(FILE *inputFile);
void hookupGraph(Graph *g, FILE *inputFile);
void printGraph(Graph *g);
int getVertexIndex(Graph *g, char *token);
void connect(Vertex *vp, Edge *ep);

// Create a graph from an input file. The format for the input file is specified
// in the graph.h header file
Graph* createGraph(FILE *inputFile)
{
  Graph *g = myMalloc(sizeof(Graph));
  g->numVertices = countLines(inputFile);
  g->numEdges = (countNumWords(inputFile)-(g->numVertices))/2;
  // init vertices
  g->vertices = myMalloc(sizeof(Vertex) * g->numVertices);
  for(int i = 0; i < g->numVertices; i++){
    Vertex *vp = g->vertices+i;
    vp->label = i+1;
    vp->head = NULL;
    vp->tail = NULL;
  }
  // init edges
  g->edges = myMalloc(sizeof(Edge) * g->numEdges);
  for(int i = 0; i < g->numEdges; i++){
    Edge *ep = g->edges+i;
    ep->endpoint1 = NULL;
    ep->endpoint2 = NULL;
  }
  hookupGraph(g, inputFile);
  return g;
}

// converts string to int and does basic error checking
int getVertexIndex(Graph *g, char *token)
{
  int vertIndex = atoi(token)-1;
  // check if vertIndex is in range
  if(vertIndex < 0 || g->numVertices-1 < vertIndex){
    fprintf(stderr, "Error parsing file: Each token in each line should be an integer in range 1 to numVertices.\n");
    exit(1);
  }
  return vertIndex;
}

// hook dat shit up yo..ahem, create ConnectorElement and connect it to the
// given edge and vertex, and vice versa
void connect(Vertex *vp, Edge *ep)
{
  // create connector element
  ConnectorElement *connector = myMalloc(sizeof(ConnectorElement));
  // connect to edge
  connector->adjacentEdge = ep;
  (ep->endpoint1) ? (ep->endpoint2 = connector) : (ep->endpoint1 = connector);
  // connect to vertex
  connector->sourceVertex = vp;
  // add to head of linked list
  connector->prev = NULL;
  connector->next = vp->head;
  if(connector->next) connector->next->prev = connector;
  vp->head = connector;
  if(vp->tail == NULL) vp->tail = connector;
}

// read through the input file and hook up the graph accordingly
void hookupGraph(Graph *g, FILE *inputFile)
{
  int maxLineLen = 1000;  // maximum length of a line in the file
  char line[maxLineLen];  // will hold one line of the file at a time
  char delim[] = " \t\r\n\f\v";
  char *token;
  int edgeIndex = 0;
  while(fgets(line, maxLineLen, inputFile)){
    // 1st token in line is the source vertex
    if((token = strtok(line, delim))){
      int vertIndex1 = getVertexIndex(g, token);
      Vertex *vert1 = g->vertices+vertIndex1;
      // loop through and add all edges/ConnectorElements
      while((token = strtok(NULL, delim))){
        int vertIndex2 = getVertexIndex(g, token);
        // if index2 < index1, then we ignore it because we already added it
        if(vertIndex1 < vertIndex2){
          Vertex *vert2 = g->vertices+vertIndex2;
          Edge *ep = g->edges+(edgeIndex++);
          connect(vert1, ep);
          connect(vert2, ep);
        }
      }
    }
  }
}

// prints the graph
void printGraph(Graph *g)
{
  printf("Num Vertices: %d\nNum Edges: %d\n", g->numVertices, g->numEdges);
  for(int i = 0; i < g->numVertices; i++){
    Vertex *vp = g->vertices+i;
    printf("Vertex %d: ", vp->label);
    ConnectorElement *curElement = vp->head;
    while(curElement != NULL){
      int v2Label;
      if(curElement->adjacentEdge->endpoint1 == curElement){
        v2Label = curElement->adjacentEdge->endpoint2->sourceVertex->label;
      } else {
        v2Label = curElement->adjacentEdge->endpoint1->sourceVertex->label;
      }
      printf("(%d,%d) ", vp->label, v2Label);
      curElement = curElement->next;
    }
    printf("\n");
  }
}

void removeEndpoint(ConnectorElement *connector)
{
  // set the edge's pointer to NULL
  if(connector->adjacentEdge->endpoint1 == connector){
    connector->adjacentEdge->endpoint1 = NULL;
  } else {
    connector->adjacentEdge->endpoint2 = NULL;
  }

  // remove from linked list
  if(connector->prev == NULL){
    connector->sourceVertex->head = connector->next;
  } else {
    connector->prev->next = connector->next;
  }
  if (connector->next == NULL) {
    connector->sourceVertex->tail = connector->prev;
  } else {
    connector->next->prev = connector->prev;
  }
  free(connector);
}

void removeEdge(Graph *g, Edge *ep)
{
  removeEndpoint(ep->endpoint1);
  removeEndpoint(ep->endpoint2);
  // put deleted edge at end of array, decrement numEdges by 1, rehookup
  // connectors
  int lastEdgeIndex = --g->numEdges;
  // if its not the last element, swap it with the last element
  if(g->edges+lastEdgeIndex != ep){
    swap(ep, g->edges+lastEdgeIndex, sizeof(Edge));
    ep->endpoint1->adjacentEdge = ep;
    ep->endpoint2->adjacentEdge = ep;
  }
}

void removeVertex(Graph *g, Vertex *vp)
{
  while(vp->head){
    removeEdge(g, vp->head->adjacentEdge);
  }
  vp->label = 0;
  int lastVertIndex = --g->numVertices;
  if(g->vertices+lastVertIndex != vp){
    swap(vp, g->vertices+lastVertIndex, sizeof(Vertex));
    ConnectorElement *curElement = vp->head;
    while(curElement != NULL){
      curElement->sourceVertex = vp;
      curElement = curElement->next;
    }
  }
}
// MANUALLY CREATE A BASIC GRAPH - same as from input1.txt
//
// Graph *g = myMalloc(sizeof(Graph));
// g->numVertices = 3;
// g->numEdges = 2;
// Vertex *vertices = myMalloc(sizeof(Vertex) * g->numVertices);
// Edge *edges = myMalloc(sizeof(Edge) * g->numEdges);
// g->vertices = vertices;
// g->edges = edges;
//
// // setup vert 1
// Vertex *vert = vertices;
// vert->label = 1;
// vert->head = myMalloc(sizeof(ConnectorElement));
// vert->tail = vert->head;
//
// edges[0].endpoint1 = vert->head;
//
// vert->head->adjacentEdge = edges;
// vert->head->sourceVertex = vert;
// vert->head->next = NULL;
// vert->head->prev = NULL;
//
// // setup vert 2
// vert = vertices+1;
// vert->label =2;
// vert->head = myMalloc(sizeof(ConnectorElement));
// vert->tail = myMalloc(sizeof(ConnectorElement));
//
// edges[0].endpoint2 = vert->head;
// edges[1].endpoint1 = vert->tail;
//
// vert->head->adjacentEdge = edges;
// vert->head->sourceVertex = vert;
// vert->head->next = vert->tail;
// vert->head->prev = NULL;
// vert->tail->adjacentEdge = edges+1;
// vert->tail->sourceVertex = vert;
// vert->tail->next = NULL;
// vert->tail->prev = vert->head;
//
// // setup vert 3
// vert = vertices+2;
// vert->label =3;
// vert->head = myMalloc(sizeof(ConnectorElement));
// vert->tail = vert->head;
//
// edges[1].endpoint2 = vert->head;
//
// vert->head->adjacentEdge = edges+1;
// vert->head->sourceVertex = vert;
// vert->head->next = NULL;
// vert->head->prev = NULL;
