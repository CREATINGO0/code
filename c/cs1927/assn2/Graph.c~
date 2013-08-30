/* Graph.c
   Written by: Angela Finlayson
Date: 15/01/09
adjacency Matrix implementation of a weighted, undirected
graph. It is assumed that the graph is connected and may
not contain self loops
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include "Graph.h"

#define NO_EDGE FLT_MAX   // represent vertices w/o edges
//between them


//Test whether a given vertex is valid
static int validV(Graph g, Vertex v) ;

//returns 1 if there is an edge from v to w
//O(1)
int isAdjacent(Graph g, Vertex v, Vertex w){
    int returnVal;
    assert(g != NULL && validV(g,v) && validV(g,w));
    if(g->adj[v][w] == NO_EDGE){
        returnVal =  0;
    }else{
        returnVal =  1;
    }
    return returnVal;
}

//returns the number of adjacent vertices
//O(V)
int adjacentVertices(Graph g, Vertex v, Vertex adj[]){
    int counter=0;
    int i=0;
    for(i=0;i<g->V;i++){
        if(g->adj[v][i] != NO_EDGE){
            adj[counter]=i;
            counter++;
        }
    }
    return counter;
}

int adjacentEdges(Graph g, Vertex v, Edge adj[]){
    int counter=0;
    int i=0;
    for(i=0;i<g->V;i++){
        if(g->adj[v][i] != NO_EDGE){
            adj[counter]=mkEdge(v,i,g->adj[v][i]);
            counter++;
        }
    }
    return counter;
}

// local checking function 
static int validV(Graph g, Vertex v) { return (v >= 0 && v < g->V); } 

// Create an edge from v to w 
Edge mkEdge(Vertex v, Vertex w, float weight) { 
    assert(v >= 0 && w >= 0); 
    Edge e = {v,w,weight}; 
    return e; 
} 

//Initialise a new graph
Graph newGraph(int nV) { 
    assert(nV >= 0); 
    int i, j; 
    Graph g = malloc(sizeof(struct graphRep)); 
    assert(g != NULL); 
    g->adj = malloc(nV * sizeof(float *)); 
    assert(g->adj != NULL); 
    for (i = 0; i < nV; i++) { 
        g->adj[i] = malloc(nV * sizeof(float)); 
        assert(g->adj[i] != NULL); 
        for (j = 0; j < nV; j++){
            g->adj[i][j] = NO_EDGE; 
        }
    } 

    g->V = nV; 
    g->E = 0; 
    return g; 
}

//Insert an edge into a graph
void insertE(Graph g, Edge e) { 
    assert(g != NULL && validV(g,e.v) && validV(g,e.w)); 

    if (e.v != e.w && g->adj[e.v][e.w]== NO_EDGE) {

        g->adj[e.v][e.w] = e.weight; 
        g->adj[e.w][e.v] = e.weight; 
        g->E++; 
    }
} 

// remove an edge from a graph
void removeE(Graph g, Edge e) { 
    assert(g != NULL && validV(g,e.v)&& validV(g,e.w)); 
    if (g->adj[e.v][e.w] != NO_EDGE) {
        g->adj[e.v][e.w] = NO_EDGE; 
        g->adj[e.w][e.v] = NO_EDGE; 
        g->E--; 
    }
} 

//Display the graph
void show(Graph g) { 
    assert(g != NULL); 
    printf("V=%d, E=%d\n", g->V, g->E); 
    int i, j; 
    for (i = 0; i < g->V; i++) { 
        int nshown = 0; 
        for (j = 0; j < g->V; j++) { 
            if (g->adj[i][j] != NO_EDGE) { 
                printf("%d-%d : %.2f ",i,j,g->adj[i][j]); 
                nshown++; 
            } 
        } 
        if (nshown > 0){
            printf("\n"); 
        }
    } 
}

//return the number of vertices in the graph
int numV(Graph g){
    assert(g != NULL);
    return g->V;
}

//return the number of edges in the graph
int numE(Graph g){
    assert(g != NULL);
    return g->E;
}


void destroyGraph(Graph g){
    int i;
    for(i=0; i< g->V; i++){
        free (g->adj[i]);
    }
    free (g->adj);

    free(g);
}
