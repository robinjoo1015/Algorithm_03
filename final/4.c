#include <stdio.h>
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
	int dist;
	int pred;
} node;

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

/* print distance and predecessor of every vertex */
void printDistPred(node graphNode[]) {
	int i;
	for(i=0;i<V;i++) {
		printf("%c.d = %d, %c.p = %c\n", 
		printVertex(i), 
		graphNode[i].dist, 
		printVertex(i), 
		printVertex(graphNode[i].pred));
	}
	printf("\n");
}

/* initialize single source */
void initialize_single_source(node graphNode[], int src) {
	int i=0;
	for(i=0;i<V;i++) {
		/* initialize array of node */
		graphNode[i].dist = INT_MAX;
		graphNode[i].pred = -1;
	}
	graphNode[src].dist = 0;
	return;
}

/* relaxation */
void relax(int u, int v, int graphWeight[][V], node graphNode[]) {
	if(graphNode[v].dist > graphNode[u].dist + graphWeight[u][v]) {
		/* update distance and predecessor */
		graphNode[v].dist = graphNode[u].dist + graphWeight[u][v];
		graphNode[v].pred = u;
	}
	return;
}

/* bellman-ford function */
bool bellman_ford(int graphWeight[][V], node graphNode[], int src) {
	int i, u, v;
	initialize_single_source(graphNode, src);
	for(i=1;i<=V-1;i++) {
		/* iterate V-1 times */
		for(u=0;u<V;u++) {
			for(v=0;v<V;v++) {
				/* check every edge */
				if(graphWeight[u][v]!=0) {
					relax(u, v, graphWeight, graphNode);
				}
			}
		}
		/* print d and pi values after each pass */
		printf("Pass %d\n", i);
		printDistPred(graphNode);
	}
	for(u=0;u<V;u++) {
		for(v=0;v<V;v++) {
			/* check every edge */
			if(graphWeight[u][v]!=0) {
				if(graphNode[v].dist > graphNode[u].dist + graphWeight[u][v]) {
					/* return FALSE if negative weight cycle exists */
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

int main() {
	/* initialize graph edge */
    int graphWeight[V][V] = {
        {0, 5, 0, 6, 0},
        {0, 0, 5, 8, -4},
        {0, -2, 0, 0, 0},
        {0, 0, -3, 0, 9},
        {2, 0, 4, 0, 0},
    };
	/* initialize graph vertex */
	node graphNode[V];
	bool noNegativeCycle = bellman_ford(graphWeight, graphNode, s);
	/* print return value of bellman-ford algorithm */
	printf("Return value of Bellman-Ford algorithm: ");
	if(noNegativeCycle) {
		printf("TRUE (No Negative Cycle Found)\n");
	} else {
		printf("FALSE (Negative Cycle Found)\n");
	}
    return 0;
}