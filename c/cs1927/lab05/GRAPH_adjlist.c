//This implements an undirected unweighted graph
//This implementation allows parallel edges

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "GRAPH.h"


typedef struct vnode *vlink;
struct vnode { 
    Vertex v; // int
    vlink next; 
};

struct graph { 
    int V; // vertex num
    int E; // edge num
    vlink *adj; // an array of linked lists 
}; // *Graph

/* 0---1  |0|->1
 *    /|  |1|->0->2->3
 *   / |  |2|->1->3
 *  /  |  |3|->1->2
 * 2---3
 */

Edge EDGE (Vertex v, Vertex w ) {
    Edge e = {v, w};
    return e;
}

int GRAPHvalidEdge(Graph g, Edge e){
    assert(g != NULL);
    return (e.v >= 0 && e.v < g->V && 
            e.w >= 0 && e.w < g->V );
}

//Creates a new node and sets the next link
vlink NEW (Vertex v, vlink next) { 
    vlink x = malloc (sizeof *x);

    x->v = v; 
    x->next = next;
    return x;                         
}

//O(V)
Graph GRAPHinit (int V) { 
    int v;
    Graph G = malloc (sizeof *G);

    G->V = V; 
    G->E = 0;

    G->adj = malloc (V * sizeof(vlink));
    for (v = 0; v < V; v++){
        G->adj[v] = NULL;
    }
    return G;
}

void GRAPHdestroy (Graph g) {

/* struct graph { int V; int E; vlink *adj; } *Graph; */
/* struct vnode { Vertex v; vlink next; } *vlink; */

    if(!g) return;

    vlink *curr;
    curr = g->adj;
    while(g->adj){
        g->adj++;
        free(curr);
        curr++;
    }

    free(g);
}


Graph GRAPHcopy(Graph g){

/* struct graph { int V; int E; vlink *adj; } *Graph; */
/* struct vnode { Vertex v; vlink next; } *vlink; */

    if(!g) return NULL; // exit if empty

    Graph bak = GRAPHinit(g->V);
    bak->E = g->E;

    int i = 0;

    while(i<=g->V){
        vlink node = (vlink)malloc(sizeof(vlink));
        node->v = g->adj[i]->v;
        bak->adj[i] = node;
        if(i!=0) bak->adj[i-1]->next = node;
        i++;
    }

    // TODO
    return bak;
}

//Undirected graph. So each edge
//is stored twice - once from v
//and once from w
//O(1)
//This does not check for parallel edges
//To do so would make it O(n)
void GRAPHinsertE(Graph G, Edge e){ 
    if(GRAPHvalidEdge(G,e) && e.v != e.w){
        int v = e.v;
        int w = e.w;

        G->adj[v] = NEW (w, G->adj[v]);
        G->adj[w] = NEW (v, G->adj[w]); 
        G->E++;
    } else {
        printf("Edge not valid ignoring ");
        GRAPHEdgePrint(e);
        printf("\n");
    }
}

int GRAPHisAdjacent(Graph g,Vertex v, Vertex w){
    vlink tmp = g->adj[v];
    int adjacent = 0;
    while(tmp != NULL && !adjacent){
        if(tmp->v == w){
            adjacent = 1;
        }
        tmp = tmp->next;
    }
    return adjacent;
}

int GRAPHadjacentVertices(Graph g, Vertex v, Vertex adj[]){
    int counter = 0;
    vlink tmp = g->adj[v];
    while(tmp != NULL){
        adj[counter] = tmp->v;
        counter++;
        tmp = tmp->next;
    }
    return counter;
}

int GRAPHedges (Edge edges[], Graph g) {
    int v, E = 0; 
    vlink t;  

    for (v = 0; v < g->V; v++) {
        for (t = g->adj[v]; t != NULL; t = t->next) {
            if (v < t->v) {
                edges[E++] = EDGE(v, t->v); 
            }
        }
    }
    return E;
}

void GRAPHEdgePrint (Edge edge) {
    printf ("%d -- %d", edge.v, edge.w);
}

int GRAPHnumV(Graph g){
    return g->V;
}

int GRAPHnumE(Graph g){
    return g->E;
}

void GRAPHshow(Graph g){
    printf("V=%d, E=%d\n", g->V, g->E); 
    int i; 
    for (i = 0; i < g->V; i++) { 
        vlink tmp = g->adj[i]; 
        while (tmp != NULL) { 
            printf("%d-%d ",i,tmp->v); 
            tmp = tmp->next; 
        } 
        if (g->adj[i] != NULL) 
            printf("\n"); 
    }
    printf("\n"); 
}
