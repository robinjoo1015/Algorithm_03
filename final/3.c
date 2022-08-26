#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef char bool;
#define TRUE (1)
#define FALSE (0)
#define V 5
#define s 0
#define t 1
#define x 2
#define y 3
#define z 4

/* struct for vertex(node) */
typedef struct node {
	/* for priority queueing */
	bool isQueue;
	int dist;
	int pred;
} node;

/* check whether priority queue is empty */
bool isEmptyQueue(node *queue) {
	int i=0;
	for(i=0;i<V;i++) {
		/* check struct member variable isQueue */
		if(queue[i].isQueue==TRUE) {
			return FALSE;
		}
	}
	return TRUE;
}

/* extract vertex from priority queue */
int extract_min(node *queue) {
	int minDist=INT_MAX, minNode=V, i=0;
	for(i=0;i<V;i++) {
		/* check with member variable isQueue */
		if(queue[i].isQueue == TRUE && queue[i].dist < minDist) {
			/* compare with member variable dist */
			minDist = queue[i].dist;
			minNode = i;
		}
	}
	/* pop minimum vertex from queue (Q = V - S) */
	queue[minNode].isQueue = FALSE;
	return minNode;
}

/* initialize single source */
void initialize_single_source(node* graphNode, int src) {
	int i=0;
	for(i=0;i<V;i++) {
		/* initialize queue (Q = G.V) */
		graphNode[i].isQueue = TRUE;
		/* initialize array of node */
		graphNode[i].dist = INT_MAX;
		graphNode[i].pred = -1;
	}
	graphNode[src].dist = 0;
	return;
}

/* relaxation */
void relax(int u, int v, int graphWeight[][V], node *graphNode) {
	if(graphNode[v].dist > graphNode[u].dist + graphWeight[u][v]) {
		/* update distance and predecessor */
		graphNode[v].dist = graphNode[u].dist + graphWeight[u][v];
		graphNode[v].pred = u;
	}
	return;
}

/* dijikstra function */
node* dijkstra(int graphWeight[][V], int src) {
	/* array containing graph info */
	node *graphNode = (node*)malloc(V*sizeof(node));
	int u, v;
	initialize_single_source(graphNode, src);
	while(isEmptyQueue(graphNode)==FALSE) {
		u = extract_min(graphNode);
		for(v=0;v<V;v++) {
			if(graphWeight[u][v]>0) {
				/* for each vertex v which are G.Adj[u] */
				relax(u, v, graphWeight, graphNode);
			}
		}
	}
	return graphNode;
}

/* returns vertex number to corresponding character */
char printVertex(int v) {
	switch(v) {
		case 0:
			return 's';
		case 1:
			return 't';
		case 2:
			return 'x';
		case 3:
			return 'y';
		case 4:
			return 'z';
		default:
			/* N for NIL */
			return 'N';
	}
}

/* print shortest path and cost to specific vertex */
void printShortestPath(int v, int src, node *result) {
	int path;
	printf("Shortest Path to %c (reversed): ", printVertex(v));
	path = v;
	/* print path in reversed order with struct member variable pred */
	while(path != src) {
		printf("%c <- ", printVertex(path));
		path = result[path].pred;
	}
	printf("%c\n", printVertex(src));
	/* print total cost of shortest path */
	printf("Total cost to %c: %d\n\n", printVertex(v), result[v].dist);
	return;
}

int main() {
	int v=0;
	/* graph with edge weight */
	int graph[V][V] = {
		{0, 3, 0, 5, 0},
		{0, 0, 6, 2, 0},
		{0, 0, 0, 0, 2},
		{0, 1, 4, 0, 6},
		{3, 0, 7, 0, 0},
	};
	node *result = dijkstra(graph, s);
	/* print shortest path and cost to y and z */
	printShortestPath(y, s, result);
	printShortestPath(z, s, result);
	return 0;
}
