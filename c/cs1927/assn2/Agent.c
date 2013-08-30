/* partially implements the Agent ADT
 * supplies the implementation for the RANDOM movement strategy 
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Agent.h"

struct agentRep{
    Vertex startLocation;
    Vertex currentLocation;
    int currentCycle;
    int maxCycles;
    float stamina;
    float maxStamina;
    int strategy;
    Graph g;
    char * name;
    int * visitcount;
    Vertex goal;
}; // Agent


Agent initAgent(Vertex start, int maxCycles,float stamina, int strategy, Graph g, char * name){
    if(start >= numV(g)){
        printf("Error starting vertex %d not valid\n",start);
        abort();
    }
    Agent agent = malloc(sizeof(struct agentRep));

    agent->startLocation = start;
    agent->currentCycle = 0;
    agent->maxCycles = maxCycles;
    agent->strategy = strategy;
    agent->currentLocation= start;
    agent->g = g;
    agent->goal = -1; //no goal
    agent->name = strdup(name);
    agent->visitcount = malloc(g->V * sizeof(int));
    int i;
    for(i=0;i<g->V;i++)
        agent->visitcount[i]=0;
    agent->stamina = stamina;  
    agent->maxStamina = stamina;

    return agent;
}


//Takes an array with all the possible edges and puts the ones the agent
//has enough stamina for into the filteredMoves array
//returns the number of filteredMoves
int filterEdges(Agent a,int numEdges,Edge *possibleMoves,Edge * filteredMoves){
    int numFiltered = 0;
    int i;
    for(i=0;i<numEdges;i++){
        if(possibleMoves[i].weight <= a->stamina){
            filteredMoves[numFiltered++] = possibleMoves[i];     
        }
    }
    return numFiltered;
}

// Get a legal move. This should be a move that the agent has enough 
// stamina to make and is a valid edge from the graph. 
// You need to implement all other strategies.
Edge getNextMove(Agent agent,Graph g){
    Edge nextMove;          
    if(agent->strategy == STATIONARY){
        nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);  
    }else if(agent->strategy == RANDOM){
        Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));
        int numEdges = adjacentEdges(g,agent->currentLocation,possibleMoves);
        int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);
        if(numFilteredEdges!= 0){
            nextMove = filteredMoves[rand()%numFilteredEdges];
            agent->stamina -= nextMove.weight;
        } else {
            nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
            agent->stamina = agent->maxStamina;
        }
        free(filteredMoves);
        free(possibleMoves);
    } else if(agent->strategy == CHEAPEST){
        Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));

        int numEdges = adjacentEdges(g,agent->currentLocation,possibleMoves);
        int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);

        int i;
        Edge * target = &filteredMoves[0];

        if(numFilteredEdges != 0){

            for(i=0;i<numFilteredEdges;i++){

                if(agent->visitcount[filteredMoves[i].w]<agent->visitcount[target->w]){
                    target = &filteredMoves[i];
                } else if(agent->visitcount[filteredMoves[i].w]==agent->visitcount[target->w]){

                    if(filteredMoves[i].weight<target->weight){
                        target = &filteredMoves[i];
                    }else if(target->weight==filteredMoves[i].weight){

                        if(filteredMoves[i].w<target->w){
                            target = &filteredMoves[i];
                        }
                    }
                }
            }

            nextMove = *target;
            agent->stamina -= nextMove.weight;
        } else {
            nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
            agent->stamina = agent->maxStamina;
        }
        free(filteredMoves);
        free(possibleMoves);
/*
    } else if( agent->strategy == DFS ){
        Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));

        int numEdges = adjacentEdges(g,agent->currentLocation,possibleMoves);
        int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);

*/
    }else {
        printf("Agent strategy not implemented yet\n");
        abort();
    }
    return nextMove;
}

//Actually perform the move, by changing the agent's state
//This function needs to be updated to adjust the agent's stamina
void makeNextMove(Agent agent,Edge move){
    agent->currentCycle++;
    agent->currentLocation = move.w;
    agent->visitcount[move.w]++;
}

Vertex getCurrentLocation(Agent agent){ return agent->currentLocation; }
char * getName(Agent agent){ return agent->name; }

//return the goal of the agent
//Only thieves start off with goals that are valid
//All other agents have a goal of -1
Vertex getGoal(Agent agent){ return agent->goal; }

void setGoal(Agent agent, Vertex goal){ agent->goal = goal; }

//Needs to be updated to print out vertex name information
//and * for cities with informants
void printAgent(Agent agent, Graph g){
    printf("%s %.2f %s (%d)",agent->name,agent->stamina, g->namae[agent->currentLocation], agent->currentLocation);
    if(agent->goal != -1){
        printf(" %s (%d)\n",g->namae[agent->currentLocation],agent->goal);
    }else{
        printf("\n");
    }
}
void destroyAgent(Agent agent){

    free(agent->name);

    free(agent);
} 
