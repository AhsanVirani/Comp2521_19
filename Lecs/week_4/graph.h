// Graph.h

#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphRep *Graph;
typedef int Vertex;

// Edges are pairs of vertices (end-points)
typedef struct Edge
{
	Vertex v; Vertex w;
} Edge;

// validity check
int validV(Graph, Vertex);
// creates an edge
Edge mkEdge(Graph, Vertex, Vertex);

// operations on graphs
Graph newGraph(int);
void insertE(Graph, Edge);
void removeE(Graph, Edge);
int neighbours(Graph, Vertex, Vertex);
int edges(Graph, Edge *, int);
void dropGraph(Graph);
void show(Graph);
void breadth_first(Graph, Vertex);
void depth_first(Graph, Vertex);
int dfsHaspPath(Graph, Vertex, Vertex);
int dfsPathFind(Graph, Vertex, Vertex, int);
void dfsFindPath(Graph, Vertex, Vertex);
void showVisited(Graph);
int dfsCycleCheck(Graph, Vertex, Vertex);
int hasCycle(Graph);
void dfsComponents(Graph, Vertex, int);
void components(Graph);
int hamiltonpathCheck(Graph, Vertex, Vertex, int);
int hamiltonpath(Graph, Vertex, Vertex);

int white_box(void);

#endif
