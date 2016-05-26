/*
 * Author: Jacob Neighbors
 * Date: 5/26/16
 * Desc: Source file for graph functions
 */

#include <stdio.h>
#include <graph.h>
#include <utilities.h>

Graph* createGraph(FILE *inputFile);
void hookupGraph(Graph *g, FILE *inputFile);
void printGraph(Graph *g);

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

void hookupGraph(Graph *g, FILE *inputFile)
{
  //TODO implement
}

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
