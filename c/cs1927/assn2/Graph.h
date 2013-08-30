// An graph ADT interface for weighted undirected graphs

/* provide interface for basic graph functionality
 * may be extended to incorporate more functionality
 * assume all graphs undirected, weighted and connected
 * assume they do not have self loops as these are a special case.
 */

// vertices denoted by integers 0..N-1 

typedef int Vertex; 

// edges are pairs of vertices (end-points) 
typedef struct { 
    Vertex v; 
    Vertex w; 
    float weight;
} Edge; 

Edge mkEdge(Vertex, Vertex, float); 

// graph representation is hidden 
typedef struct graphRep *Graph; 
struct graphRep { 
    int V;          // #vertices 
    int E;          // #edges 
    char * joho;    // informants
    char namae[20][100];  // name array of cities
    float ** adj;   // matrix of weights
}; // Graph

// operations on graphs 
Graph newGraph(int nV); // #vertices 
void insertE(Graph g, Edge e); 
void removeE(Graph g, Edge e); 

//returns 1 if there is ad adge from v to w
int isAdjacent(Graph g,Vertex v, Vertex w);
int adjacentVertices(Graph g, Vertex v, Vertex adj[]);
int adjacentEdges(Graph g, Vertex v, Edge adj[]);

// returns #vertices & array of edges int
int edges(Edge es[], int nE, Graph g); 

int numV(Graph g);
int numE(Graph g);

void destroyGraph(Graph g); 
void show(Graph g); 
