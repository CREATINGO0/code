/**
  main.c
  Written by:Angela Finlayson
Date: 16/01/09
Modified: 9/01/2013
The client game. This reads in data from a file to create a graph that
represents a map of cities. 
It reads in data to create 5 agents: a thief and 4 detectives. 
It then runs a simulation where the thief and detectives move
through the cities. 
Currently only a random movement strategy has been implemented.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "Graph.h"
#include "Agent.h"

#define MAXLINE 20

#define NUM_DETECTIVES 4
#define THIEF 0
#define D1 1
#define D2 2
#define D3 3
#define D4 4

#define DEBUG 0

//Game states
#define CONTINUE 0
#define WIN -1
#define LOSE -2
#define OVER -3

Graph readGraph(char * filename);
void initialiseAgents(char *filename, Agent agents[], int maxCycles, Graph g);
void display(int cycle,Agent agents[],Graph g);
int checkGameState(Agent agents[],Graph g,int cycle,int maxCycles);
int step(int cycle,Agent agents[],Graph g,int maxCycles);
int run(int cycle, int maxCycles, Agent agents[],Graph g);
void stats(int cycle, Agent agents[], Graph g);
void freeResources(Agent agents[],Graph g);

int main(int argc, char * argv[]){

    // cityinfo, agentinfo, cycles, seed

    Agent agents[NUM_DETECTIVES+1];

    if(argc < 4){
        printf("Incorrect usage: please enter filename1 filename2 maxCycles\n");
        exit(0);
    }

    int maxCycles = atoi(argv[3]);

    int cycle = 0;
    int seed = time(NULL);

    if(argc == 5) 
        seed = atoi(argv[4]);

    srand(seed);
    Graph g = readGraph(argv[1]);
    initialiseAgents(argv[2],agents,maxCycles,g);
#ifdef DEBUG
    stats(cycle,agents,g);
    printf("maxCycles = %d\n",maxCycles);
#endif

    char command[MAXLINE];
    printf("\nPOLICE ACADEMY 1927");
    printf("\n\nRed alert! A thief is on the run.\n");
    printf("Agents, to your cars. You have %d hours.\n\n",maxCycles);
    display(cycle,agents,g);

    if(checkGameState(agents,g,cycle,maxCycles) != CONTINUE){
        freeResources(agents,g);
        return 0;
    }
    printf("Enter command: ");
    scanf("%s",command);


    while (strcmp(command,"quit") != 0){
        if(strcmp(command,"display") == 0){
            display(cycle,agents,g);
        }else if(strcmp(command,"run") == 0){
            cycle = run(cycle,maxCycles,agents,g);
        }else if(strcmp(command,"step") == 0){
            cycle = step(cycle,agents,g,maxCycles);
        }else if(strcmp(command,"stats") == 0){
            stats(cycle,agents,g);
        }else if(strcmp(command,"map") == 0){
            show(g);
            printf("\n");
        }
        if(cycle < 0) break;
        printf("Enter command: ");
        scanf("%s",command);
    }
    freeResources(agents,g);
    return 0;
}

//Reads in data from the file with the given filename and creates a newGraph
//The file must be of the format
//numVertices
//v1 v2 weight v1 v2 weight informant cityname
//v1 v2 weight v1 v2 weight informant cityname
Graph readGraph(char * filename) {
    FILE *fp;
    fp = fopen (filename, "r"); // cityinfo
    assert (fp != NULL);

    int city = 0;
    int dest = 0;
    double weight = 0;
    //char c = 0;
    //First line of file has the number of vertices
    int numV;
    fscanf(fp, "%d", &numV);

    Graph g = newGraph(numV);   
    // scan through file and insert edges into graph
    int counter=0; 
    char informant; 
    char name[100];
    char johosha[numV];
    while (counter < numV) {
        fscanf(fp,"%d",&city);
        while(fscanf(fp, "%d %lf", &dest,&weight) == 2){
            insertE(g,mkEdge(city, dest, weight));
        }
        //TASK 0 - YOU MUST STORE THIS INFO IN THE GRAPH
        fscanf(fp,"%c %[^\n]",&informant,name);
        johosha[counter] = informant;
        strcpy(g->namae[counter],name);
        counter++;
    }
    g->joho = johosha;
    fclose(fp);
    return g;
}

// initialises the thief and 4 detectives from a data file
void initialiseAgents(char *filename, Agent agents[], int maxCycles, Graph g){
    FILE *fp;
    fp = fopen (filename, "r"); // open data file
    assert (fp != NULL);
    float stamina;
    Vertex start;
    Vertex end;
    char name[5]; // T, D1, D2...
    int i;
    int strategy;

    fscanf(fp, "%f %d %d %[^\n]", &stamina,&start,&end,name);
    agents[THIEF] = initAgent(start,maxCycles,stamina,RANDOM,g,name);
    setGoal(agents[THIEF],end);
    for(i=1;i<=NUM_DETECTIVES;i++){      
        fscanf(fp, "%f %d %d %[^\n]", &stamina,&start,&strategy,name);
        agents[i] = initAgent(start,maxCycles,stamina,strategy,g,name);    
    }  
    fclose(fp);
}

//Display information about the current state of the game
void display(int cycle,Agent agents[],Graph g){
    int i;
    printf("Hour %d\n",cycle);
    // function to print the current location of each agent
    printf ("  T  D1  D2  D3  D4\n");
    for (i = 0; i <= NUM_DETECTIVES; i++) {    
        printf ("%3d", getCurrentLocation(agents[i]));
        printf(" ");
    }
    puts("\n");
}


//check whether the game is over
int checkGameState(Agent agents[],Graph g,int cycle,int maxCycles){
    if(cycle >= maxCycles){
        printf("GAME OVER: YOU LOSE - TIME IS UP\n");
        return OVER;
    } else if( getCurrentLocation(agents[THIEF]) == getCurrentLocation(agents[D1]) ) {
        printf("D1 caught the thief in %s (%d)\nYOU WIN - THIEF CAUGHT!\n",
                g->namae[getCurrentLocation(agents[THIEF])],getCurrentLocation(agents[THIEF]));
        return WIN;
    } else if( getCurrentLocation(agents[THIEF]) == getCurrentLocation(agents[D2]) ) {
        printf("D2 caught the thief in %s (%d)\nYOU WIN - THIEF CAUGHT!\n",
                g->namae[getCurrentLocation(agents[THIEF])],getCurrentLocation(agents[THIEF]));
        return WIN;
    } else if( getCurrentLocation(agents[THIEF]) == getCurrentLocation(agents[D3]) ) {
        printf("D3 caught the thief in %s (%d)\nYOU WIN - THIEF CAUGHT!\n",
                g->namae[getCurrentLocation(agents[THIEF])],getCurrentLocation(agents[THIEF]));
        return WIN;
    } else if( getCurrentLocation(agents[THIEF]) == getCurrentLocation(agents[D4]) ) {
        printf("D4 caught the thief in %s (%d)\nYOU WIN - THIEF CAUGHT!\n",
                g->namae[getCurrentLocation(agents[THIEF])],getCurrentLocation(agents[THIEF]));
        return WIN;
    } else if( getCurrentLocation(agents[THIEF]) == getGoal(agents[THIEF]) ) {
        printf("T got away to %s (%d).\n",
                g->namae[getCurrentLocation(agents[THIEF])],getCurrentLocation(agents[THIEF]));
        puts("GAME OVER: YOU LOSE - THIEF GOT TO GATEWAY");
        return LOSE;
    } else {
        return CONTINUE;
    }
}

//step through one cycle of the game
int step(int cycle,Agent agents[],Graph g,int maxCycles){

    int i;
    cycle++;
    for(i=0;i<=NUM_DETECTIVES;i++){
        Edge  nextMove = getNextMove(agents[i],g);  
        makeNextMove(agents[i],nextMove);
    }
    display(cycle,agents,g);
    int gameState = checkGameState(agents,g,cycle,maxCycles);
    if(gameState == CONTINUE){
        return cycle;
    } else {
        return gameState;
    }
}


int run(int cycle, int maxCycles, Agent agents[],Graph g){
    while(cycle < maxCycles && cycle >= 0){
        cycle = step(cycle,agents,g,maxCycles);
    }
    return cycle;
}


void stats(int cycle, Agent agents[],Graph g){
    int i;
    printf("Hour %d\n",cycle);
    for(i=0;i<=NUM_DETECTIVES;i++){
        printAgent(agents[i],g);
    } 
    printf("\n");
}

void freeResources(Agent agents[], Graph g){
    int i;
    for(i=0;i<=NUM_DETECTIVES;i++){
        destroyAgent(agents[i]);
    }
    destroyGraph(g);
}
