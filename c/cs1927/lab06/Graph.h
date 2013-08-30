// A graph ADT interface.
// This will need to be modified for lab07


// vertices denoted by integers 0..N-1 
typedef int Vertex; 
typedef struct edge Edge;

// edges are pairs of vertices (end-points) 
struct edge{ 
    Vertex v; 
    Vertex w; 
} ; 

Edge mkEdge(Vertex, Vertex); 

// graph representation is hidden 
typedef struct graphRep *Graph; 

int isAdjacent(Graph g,Vertex v1, Vertex v2);

// operations on graphs 
Graph newGraph(int nV); // #vertices 
void insertE(Graph g, Edge e); 
void removeE(Graph g, Edge e); 

// returns #vertices & array of edges int
int edges(Edge es[], int nE, Graph g); 

int numV(Graph g);
int numE(Graph g);

void destroyGraph(Graph g); 
void showGraph(Graph g);

//Search functions
void dfSearch(Graph g);

//Functions to show results of search functions
void printPre(Graph g);
void printSt(Graph g, Vertex start, Vertex end);

//These functions need to be implemented

// should print out edges in graph using the vertex names
// Australia Tonga rather than vertex numbers.
void showGraphLabels(Graph g);

// Should print out the data associated with each vertex in the graph
void showData(Graph g);

// Should print out the data associate with one vertex in the graph
void showVertexData(Graph g, Vertex v);  

// Should return the vertex label of a given vertex
// eg 0 - China
char *getVertexLabel(Graph g, Vertex v);

// dfsOrder should contain each vertex as it is discovered in order
void dfSearch2(Graph g, int *dfsOrder);
