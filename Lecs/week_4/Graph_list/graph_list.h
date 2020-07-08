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


// operations on graphs
Graph newGraph(int);
// check validity of a Vertex
int validV(Graph, Vertex);
// creates an Edge
Edge mkEdge(Graph, Vertex, Vertex);
// insert an edge into the graph
void insertE(Graph, Edge);
// remove an edge from the graph
void removeE(Graph, Edge);
// Display the graph
void showGraph(Graph);
// checks whether an edge exist between 2 vertices
int adjacent(Graph, Vertex, Vertex);
// drop graph and free memory allocated
void dropGraph(Graph);

#endif
