#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAPSIZE 20
#define TASKCOUNT 1000

int main() {

    int i = TASKCOUNT;
    srand(time(NULL));

    while(i>0) {
        printf("Job %d %d to %d %d\n",\
        	rand()%MAPSIZE,rand()%MAPSIZE,rand()%MAPSIZE,rand()%MAPSIZE);
        i--;
    }
    return 0;
}
