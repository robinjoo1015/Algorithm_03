#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef char bool;
#define TRUE (1)
#define FALSE (0)
#define V 8
#define r 0
#define s 1
#define t 2
#define u 3
#define v 4
#define w 5
#define x 6
#define y 7
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_QUEUE 100

/* struct for vertex(node) */
typedef struct node {
    int color;
    int dist;
    int pred;
} node;

/* global queue */
int queue[MAX_QUEUE];
int head=0;
int tail=0;

/* is queue empty */
bool isEmpty() {
    if(head==tail) { return TRUE; }
    else { return FALSE; }
}

/* push element to queue */
void enqueue(int push) {
    queue[tail++] = push;
    tail %= MAX_QUEUE;
}

/* pop element from queue */
int dequeue() {
    int pop = queue[head++];
    head %= MAX_QUEUE;
    return pop;
}

/* initialize graph node */
void initGraphNode(node *graphNode, int src) {
    int i;
    for(i=0;i<V;i++) {
        graphNode[i].color = WHITE;
        graphNode[i].dist = INT_MAX;
        graphNode[i].pred = -1;
    }
    graphNode[src].color = GRAY;
    graphNode[src].dist = 0;
    graphNode[src].pred = -1;
    return;
}

node* BFS(int graph[][V], int src) {
    int a, b, i;
    node *graphNode = (node*)malloc(V*sizeof(node));
    /* initialize graph node */
    initGraphNode(graphNode, src);
    /* push source vertex to queue */
    enqueue(src);
    while(isEmpty()==FALSE) {
        a = dequeue();
        for(b=0;b<V;b++) {
            if(graph[a][b]==1) {
                if(graphNode[b].color == WHITE) {
                    graphNode[b].color = GRAY;
                    graphNode[b].dist = graphNode[a].dist + 1;
                    graphNode[b].pred = a;
                    enqueue(b);
                }
            }
        }
        graphNode[a].color = BLACK;
    }
    return graphNode;
}

/* returns vertex number to corresponding character */
char printVertex(int n) {
	switch(n) {
		case 0:
			return 'r';
		case 1:
			return 's';
		case 2:
			return 't';
		case 3:
			return 'u';
		case 4:
			return 'v';
        case 5:
			return 'w';
        case 6:
			return 'x';
        case 7:
			return 'y';
        default:
            /* N for NIL */
            return 'N';
	}
}

int main() {
    int i;
    /* array of edges of graph */
    int graph[V][V] = {
        {0,1,0,0,1,0,0,0},
        {1,0,0,0,0,1,0,0},
        {0,0,0,1,0,1,1,0},
        {0,0,1,0,0,0,1,1},
        {1,0,0,0,0,0,0,0},
        {0,1,1,0,0,0,1,0},
        {0,0,1,1,0,1,0,1},
        {0,0,0,1,0,0,1,0},
    };
    node *graphNode = BFS(graph, s);
    for(i=0;i<V;i++) {
        /* print d and pi for all vertex */
        printf("%c.d = %d, %c.p = %c\n", 
            printVertex(i), 
            graphNode[i].dist, 
            printVertex(i), 
            printVertex(graphNode[i].pred)
            );
    }
    return 0;
}