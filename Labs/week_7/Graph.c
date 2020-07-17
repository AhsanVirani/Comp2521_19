// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"

#define MAX_NUM 100000000

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	Edge new = {v, w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w, int wt)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = wt;
	g->edges[w][v] = wt;
	g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		// an edge doesn't exist; do nothing.
		return;

	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

// create an empty graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = nV, .nE = 0 };

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}

// display graph, using names for vertices
void showGraph (Graph g, char **names)
{
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf ("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf ("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf ("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath (Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert (g != NULL && validV(g, src) && validV(g, dest));
	
	// Path of length 1 i.e. src to src
	if(src == dest) {
		path[0] = src;
		return 1;
	}

	int *dist = calloc(g->nV, sizeof(int));
	int *visited = calloc(g->nV, sizeof(int));
	int *pathcpy = malloc(g->nV * sizeof(int));
	int i;
	for(i = 0; i < g->nV; i++)	pathcpy[i] = -1;

	Queue q = newQueue();
	QueueJoin(q, src);
	pathcpy[src] = 0;


	int PATH_FOUND = 0;	
	while(!QueueIsEmpty(q)) {
		Item v = QueueLeave(q);
		if(PATH_FOUND) break;
		Vertex w;	
		for(w=0; w < g->nV; w++) {
			if(!g->edges[v][w] || g->edges[v][w] > max)	continue;
			if(!visited[w]) {
				visited[w] = 1;
				QueueJoin(q, w);
				dist[w] = dist[v] + 1;
				pathcpy[w] = v;
				if(w == dest) {
					PATH_FOUND = 1;
					break;
				}
			}
		}
	}

	if(dist[dest] > 0) {
		i = dist[dest];
		printf("%d\n", dist[dest]);	
		path[i] = dest;
		i--;
		int destcpy = dest;
		while(i >= 0) {
			path[i] = pathcpy[destcpy];
			destcpy = pathcpy[destcpy];
			i--;			
		}
		free(dist); free(visited); free(pathcpy);
		// Path found of length > 1
		return dist[dest]+1;
	}
	free(dist); free(visited); free(pathcpy);
	
	// No path found
	return 0;
}

