#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph_list.h"
#include "List.h"


typedef struct GraphRep
{
	int nV;
	int nE;
	List *edges; // adjacency list rep. Edge is a verticle array of pointers storing ListRep
} GraphRep;


// create new empty graph
Graph newGraph(int nV)
{
	assert(nV >= 0);
	Graph g = (Graph)malloc(nV*sizeof(GraphRep));
	assert(g != NULL);
	List *e = (List *)malloc(nV*sizeof(List));
	assert(e != NULL);
	
	for(int i = 0; i < nV; i++) {
		e[i] = newList();
	}
 
	g->nV = nV; g->nE = 0; g->edges = e;
	return g;
} 

// Check validaity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// creates an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(validV(g, v) && validV(g, w));
	Edge e;
	e.v = v;	e.w = w;
	return e;
}

// create a new Edge
void insertE(Graph g, Edge e)
{
	assert(validV(g, e.v) && validV(g, e.w));
	if(ListSearch(g->edges[e.v], e.w) != NULL)	return;
	ListInsert(g->edges[e.v], e.w);
	ListInsert(g->edges[e.w], e.v);
	g->nE++;	
}

// remove an edge from the graph
void removeE(Graph g, Edge e)
{
	assert(validV(g, e.v) && validV(g, e.w));
	if(ListSearch(g->edges[e.v], e.w) == NULL)	return;
	ListDelete(g->edges[e.v], e.w);
	ListDelete(g->edges[e.w], e.v);
	g->nE--;
}

// Checks whether two vertices are directly connected
int adjacent(Graph g, Vertex v, Vertex w)
{
	assert(validV(g, v) && validV(g, w));
	return (ListSearch(g->edges[v], w) != NULL);
}

// Display the graph
void showGraph(Graph g)
{
	assert(g != NULL);
	printf("nV:%d nE:%d\n", g->nV, g->nE);
	for(int i =0; i < g->nV; i++) {
		printf("Vertex %d is connected to ", i);
		showList(g->edges[i]);
		printf("\n");
	}
}

// drop the graph and free memory occupid
void dropGraph(Graph g)
{
	assert(g != NULL);
	for(int i = 0; i < g->nV; i++)
		dropList(g->edges[i]);
	free(g->edges);
	free(g);
}


int main(void)
{
	// Creates a new empty graph with 3 vertices
	Graph g = newGraph(4);
	
	// Make graph from Lab example
	Edge e1 = mkEdge(g, 0, 1);
	Edge e2 = mkEdge(g, 1, 2);
	Edge e3 = mkEdge(g, 1, 3);
	Edge e4 = mkEdge(g, 2, 3);

	// Adding edges and displaying Graph
	insertE(g, e1);
	insertE(g, e2);
	insertE(g, e3);
	insertE(g, e4);
	insertE(g, e4);
	showGraph(g);
	// Removing edges and displaying Graph
	removeE(g, e4);
	removeE(g, e1);
	removeE(g, e1);
	showGraph(g);
	// checking adjacent
	if(adjacent(g, 1, 2))	printf("Edge from 1 - 2\n");
	if(adjacent(g, 2, 3))	printf("Edge from 2 - 3\n");

	dropGraph(g);
	
	return 0;
}
