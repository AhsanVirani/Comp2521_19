// Graph implementation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "graph.h"
#include "Queue.h"
#include "Stack.h"
#include "Item.h"

// Global Variables
int order;
int *visited;

// Graph Representation (Adjacency Matrix)
typedef struct GraphRep
{
	int nV;	// #vertices
	int nE;	// #Edges
	int **edges;	// matrix of booleans (2d array)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// create an Edge value
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(validV(g, v) && validV(g, w));
	Edge e;
	e.v = v;	e.w = w;
	return e;
}

// create and empty graph
Graph newGraph(int nV)
{
	assert(nV >= 0);
	int i;
	int **e = malloc(nV * sizeof(int *));
	assert(e != NULL);
	for(i = 0; i < nV; i++)	
	{		
		e[i] = calloc(nV, sizeof(int));	
		assert(e[i] != NULL);
	}
	Graph g = malloc(sizeof(GraphRep));
	assert(g != NULL);
	g->nV = nV; g->nE = 0; g->edges = e;
	return g;
}

// Breadth first traversal
void breadth_first(Graph g, Vertex st)
{
	assert(validV(g, st));
	visited = calloc(g->nV, sizeof(int));
	assert(visited != NULL);
	
	Queue q = newQueue();
	QueueJoin(q, st);
	while(!QueueIsEmpty(q)) {
		Vertex v = QueueLeave(q);
		if(visited[v])	
			continue;
		visited[v] = 1;
		printf("%d\n", v);
		for(Vertex i = 0; i < g->nV; i++) {
			if(!g->edges[v][i])
				continue;
			if(!visited[i])
				QueueJoin(q, i);	
		}
	}
}

// Depth first traversal
void depth_first(Graph g, Vertex st)
{
	assert(validV(g, st));
	visited = calloc(g->nV, sizeof(int));
	assert(visited != NULL);

	Stack s = newStack();
	StackPush(s, st);
	while(!StackIsEmpty(s)) {
		Vertex v = StackPop(s);
		if(visited[v])	continue;
		visited[v] = 1;
		printf("%d\n", v);
		for(Vertex i = g->nV - 1; i >= 0; i--) {
			if(!g->edges[v][i])	continue;
			if(!visited[i])
				StackPush(s, i);
		}
	}
}

// wrapper for recursive DFS func
void depth_first_R(Graph g, Vertex st)
{
	assert(validV(g, st));
	visited = calloc(g->nV, sizeof(int));
	depth_first_wrapper_R(g, st);
	printf("\n");
	free(visited);
}

void depth_first_wrapper_R(Graph g, Vertex st)
{
	printf("%d", st);	
	visited[st] = 1;

	Vertex w;
	for(w = 0; w < g->nV; w++) {
		if(!neighbours(g, st, w)) continue;
		if(visited[w])	continue;
		printf("->");
		depth_first_wrapper_R(g, w);
	}
	return;
}

// add a new edge
void insertE(Graph g, Edge e)
{
	assert(g != NULL);
	assert(validV(g, e.v) && validV(g, e.w));
	if(g->edges[e.v][e.w])	return;
	g->edges[e.v][e.w] = 1;
	g->edges[e.w][e.v] = 1;
	g->nE++;
}

// Remove an edge
void removeE(Graph g, Edge e)
{
	assert(g != NULL);
	assert(validV(g, e.v) && validV(g, e.w));
	if(!g->edges[e.v][e.w])	return;
	g->edges[e.v][e.w] = 0;
	g->edges[e.w][e.v] = 0;
	g->nE--;
}

// are two vertices directly connected?
int neighbours(Graph g, Vertex x, Vertex y)
{
	assert(validV(g, x) && validV(g, y));
	return (g->edges[x][y]);
}

// returns #edges & array of edges
int edges(Graph g, Edge *es, int nE)
{
	assert(g != NULL && nE >= 0);
	int n = 0;
	for(int i = 0; i < g->nV; i++)
	{		
		for(int j = i+1; j < g->nV; j++)
		{
			if(n == nE)	return n;
			if(g->edges[i][j] == 1)
			{
				es[n] = mkEdge(g, i, j);
				n++;
			} 
		}
	}
	return 0;
}

// Free memory associated with Graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	for(int i = 0; i < g->nV; i++)	free(g->edges[i]);
	free(g->edges);
	free(g);
}

// display a graph
void show(Graph g)
{
	assert(g != NULL);
	printf("Graph has V=%d and E=%d\n", g->nV, g->nE);	
	printf("V	connected to\n");
	printf("--	------------\n");
	int v, w;
	for(v = 0; v < g->nV; v++)
	{
		printf("%-3d ", v);
		for(w = 0; w < g->nV; w++)
		{
			if(g->edges[v][w])	printf(" %d", w);
		}
		printf("\n");
	}
}

void showVisited(Graph g)
{
	int i;
	for(i = 0; i < g->nV; i++)
		printf("[%d]=%d ", i, visited[i]);
	printf("\n");

}

// DFS path checker. A wrapper for dfsHasPath
int dfsPathCheck(Graph g, Vertex v, Vertex dest)
{
	visited[v] = 1;
	Vertex w;
	for(w = 0; w < g->nV; w++)
	{
		if(!g->edges[v][w])	continue;
		if(w == dest)	return 1;
		if(!visited[w])
		{
			if(dfsPathCheck(g, w, dest))	return 1;
		}
	}
	return 0;
}

int *path;

int dfsHaspPath(Graph g, Vertex src, Vertex dest)
{
	visited = calloc(g->nV, sizeof(int));
	int results = dfsPathCheck(g, src, dest);
	free(visited);
	return results;
}

int dfsPathFind(Graph g, Vertex v, Vertex dest, int ord)
{
	printf("pf(g,%d,%d,%d)\n", v, dest, ord);
	visited[v] = 1;
	path[ord] = v;
	if(v == dest)	return 1;
	Vertex w;
	for(w = 0; w < g->nV; w++)
	{
		if(!g->edges[v][w])	continue;
		if(!visited[w])
		{
			if(dfsPathFind(g, w, dest, ord+1))	return 1;
		}
			else	path[ord+1] = -1;
	}
	return 0;
}

void dfsFindPath(Graph g, Vertex src, Vertex dest)
{
	int i;
	visited = calloc(g->nV, sizeof(int));
	path = malloc((g->nV+1) * sizeof(Vertex));
	for(i = 0; i <= g->nV; i++)	path[i] = -1;
	if(!dfsPathFind(g, src, dest, 0))
		printf("No path from %d to %d\n", src, dest);
	else
	{
		printf("Path: %d", path[0]);
		for(i = 1; path[i] != -1; i++)	
			printf("->%d", path[i]);
		printf("\n");		
	}
	free(visited); free(path);
}

int dfsCycleCheck(Graph g, Vertex v, Vertex prev)
{
	printf("v=%d vis: ", v);	showVisited(g);
	visited[v] = 1;
	Vertex w;
	for(w = 0; w < g->nV; w++) {
		if(g->edges[v][w]) {
			printf("edge %d-%d\n", v, w);
			if(!visited[w])
				return dfsCycleCheck(g, w, v);
			else if(w != prev)
				return 1;
		}
	}
	return 0;
}

int hasCycle(Graph g)
{
	visited = calloc(g->nV, sizeof(int));
	int result = dfsCycleCheck(g, 0, 0);
	free(visited);
	return result;
}

int *componentOf;
int ncounted;

void dfsComponents(Graph g, Vertex v, int c)
{
	componentOf[v] = c;
	ncounted++;
	Vertex w;
	for(w = 0; w < g->nV; w++) {
		if(g->edges[v][w] && componentOf[w] == -1)
			dfsComponents(g, w, c);
	}
}

void components(Graph g)
{
	int i, compID = 0;
	componentOf = malloc(g->nV*sizeof(int));
	for(i = 0; i < g->nV; i++)	componentOf[i] = -1;
	ncounted = 0;
	while(ncounted < g->nV) {
		Vertex v;
		for(v = 0; v < g->nV; v++)
			if(componentOf[v] == -1)	break;
		dfsComponents(g, v, compID);		
		compID++;
	}
	for(i = 0; i < compID; i++) {
		printf("Component %d has", i);	
		int v;
		for(v = 0; v < g->nV; v++) {
			if(componentOf[v] == i)
				printf(" %d", v);
		}
		printf("\n");
	}

}

int hamiltonpathCheck(Graph g, Vertex v, Vertex w, int counter)
{
	// pass scene
	int t;
   if (v == w)	return counter == 0? 1 : 0;
	else if(v == w && counter != 0) return 0;
	visited[v] = 1;
	for(t = 0; t < g->nV; t++) {
		if(!neighbours(g, v, t)) continue;
		if(visited[t] == 1)	continue;
		if(hamiltonpathCheck(g, t, w, counter-1))	return 1;
	}
	visited[v] = 0;
	return 0;
}

int hamiltonpath(Graph g, Vertex src, Vertex dest)
{
	assert(g != NULL && validV(g, src) && validV(g, dest));
	visited = calloc(g->nV, sizeof(int));
	assert(visited != NULL);	
	int res = hamiltonpathCheck(g, src, dest, g->nV-1);
	free(visited);
	return res;
}

/*
bool isEulerPath (Graph g, Edge e[], int nE)
{



}
*/

int white_box(void)
{
	Graph g = newGraph(7);
	//show(g);
	Edge e1 = mkEdge(g, 0, 1);
	Edge e2 = mkEdge(g, 0, 3);
	Edge e3 = mkEdge(g, 0, 4);
	Edge e4 = mkEdge(g, 0, 5);
	Edge e5 = mkEdge(g, 1, 5);
	Edge e6 = mkEdge(g, 2, 3);
	Edge e7 = mkEdge(g, 2, 5);
	Edge e8 = mkEdge(g, 2, 6);
	Edge e9 = mkEdge(g, 4, 5);
	Edge e10 = mkEdge(g, 5, 6);

	insertE(g, e1);
	insertE(g, e2);
	insertE(g, e3);
	insertE(g, e4);
	insertE(g, e5);
	insertE(g, e6);
	insertE(g, e7);
	insertE(g, e8);
	insertE(g, e9);
	insertE(g, e10);
	
	//show(g);
	//printf("\n");
	depth_first(g, 1);
	depth_first_R(g, 1);

	return 0;
}



