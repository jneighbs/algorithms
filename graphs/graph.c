/*
 * Author: Jacob Neighbors
 * Date: 5/26/16
 * Desc: Source file for graph functions
 */

#include <stdio.h>
#include <graph.h>

Graph* createGraph(FILE *inputFile)
{
  // TODO: implement!
  return NULL;
}


// TODO - need to test this
void printGraph(Graph *g)
{

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
