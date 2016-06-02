/*
 * Author: Jacob Neighbors
 * Date: 5/26/16
 * Desc: Source file for graph functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <graph.h>
#include <utilities.h>

Graph* createGraph(FILE *inputFile);
void hookupGraph(Graph *g, FILE *inputFile);
void printGraph(Graph *g);
int getVertexIndex(Graph *g, char *token);
void connect(Vertex *vp, Edge *ep, ConnectorElement *con);
void removeEndpoint(ConnectorElement *connector);
void removeEdge(Graph *g, Edge *ep);
void removeVertex(Graph *g, Vertex *vp);
int kargerMinCut(FILE *inputFile, int numIterations);
int runKarger(Graph *g);

/*
TODO:
  1) reorganize connectorElements so that they are initialized in 1 big array
    of size 2*numEdges. That way they are easy to copy over into another graph
    (and also easier to free)

  2) write a free(graph) functions

  3)write a copyGraph(g) function

  4) make kargerMinCut take a graph again as an argument instead of a file.

*/

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
  //init connector elements
  g->connectors = myMalloc(sizeof(ConnectorElement) * g->numEdges * 2);
  for(int i = 0; i < g->numEdges*2; i++){
    ConnectorElement *connector = g->connectors+i;
    connector->adjacentEdge=NULL;
    connector->sourceVertex=NULL;
    connector->prev=NULL;
    connector->next=NULL;
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

// hook dat shit up yo..ahem, connect  the ConnectorElement to the given
// edge and vertex, and vice versa
void connect(Vertex *vp, Edge *ep, ConnectorElement *con)
{
  // connect to edge
  con->adjacentEdge = ep;
  (ep->endpoint1) ? (ep->endpoint2 = con) : (ep->endpoint1 = con);
  // connect to vertex
  con->sourceVertex = vp;
  // add to head of linked list
  con->next = vp->head;
  if(con->next) con->next->prev = con;
  vp->head = con;
  if(vp->tail == NULL) vp->tail = con;
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
          Edge *ep = g->edges+edgeIndex;
          ConnectorElement *con = g->connectors+(2*edgeIndex);
          connect(vert1, ep, con);
          con = g->connectors+(2*edgeIndex+1);
          connect(vert2, ep, con);
          edgeIndex++;
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

// removes the connector element
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

  // set to NULL
  connector->adjacentEdge=NULL;
  connector->sourceVertex=NULL;
  connector->prev=NULL;
  connector->next=NULL;
}

// removes an edge from the graph
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

// Removes a vertex from the graph (and its edges)
void removeVertex(Graph *g, Vertex *vp)
{
  // while it has edges, remove them
  while(vp->head){
    removeEdge(g, vp->head->adjacentEdge);
  }
  vp->label = 0;
  // swap vert out to end of array, fix pointers
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

int kargerMinCut(FILE *inputFile, int numIterations)
{
  time_t t;
  srand((unsigned)time(&t));
  Graph *g = createGraph(inputFile);
  rewind(inputFile);
  int bestSolution = g->numEdges;
  for(int i = 0; i < numIterations; i++){
    g=createGraph(inputFile);
    rewind(inputFile);
    int newSolution = runKarger(g);
    if(newSolution < bestSolution) bestSolution = newSolution;
  }
  return bestSolution;
}

int runKarger(Graph *g)
{
  while(g->numVertices > 2){
    // pick edge at random
    Edge *ep = g->edges+(rand()%g->numEdges);
    //grab the edges 2 vertices
    Vertex *v1 = ep->endpoint1->sourceVertex;
    Vertex *v2 = ep->endpoint2->sourceVertex;
    // printf("Conracting edge (%d,%d)\n", v1->label, v2->label);
    // add v2's list onto the end of v1
    v1->tail->next = v2->head;
    v2->head->prev = v1->tail;
    v1->tail = v2->tail;
    v2->head = NULL;
    v2->tail = NULL;

    // loop through linked list, point them all to v1, delete self loops
    ConnectorElement *curElement = v1->head;
    while(curElement){
      curElement->sourceVertex = v1;
      Edge *edgeToCheck = curElement->adjacentEdge;
      curElement = curElement->next;
      // if I got really unlucky and switched to a connector element that shares
      // the same edge as the prev element, I need to switch again
      if(curElement && curElement->adjacentEdge==edgeToCheck){
        curElement->sourceVertex = v1;
        curElement = curElement->next;
      }
      // if its a self loop, remove edge
      if(edgeToCheck->endpoint1->sourceVertex==v1 && edgeToCheck->endpoint2->sourceVertex==v1){
        removeEdge(g, edgeToCheck);
      }
    }
    removeVertex(g, v2);
  }
  return g->numEdges;
}
