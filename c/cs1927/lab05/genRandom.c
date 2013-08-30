#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int i, numElements;

    if(argc > 1){
        numElements = atoi(argv[1]);
    } else{
        fprintf(stderr,"Usage ./genRandom n\n");
        abort();
    }
    
    //print out number of elements
    printf("%d\n",numElements);
    // Generate random data
    srand(time(NULL));
    
    for (i = 0; i < numElements; i++) { // Randomly generate data
         printf("%d\n",rand()%1000000);
    }
    return 0;
}
