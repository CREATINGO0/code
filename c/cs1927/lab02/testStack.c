#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Item.h"
#include "Stack.h"

//This function should contain
//tests that have access to the internal structure 
//of the stack. It should be implemented in arrayStack.c

void whiteBoxTests(void);

struct stackImp{
    Item * items; // int
    int top;
    int maxSize;
};

int main (int argc, char *argv[]){
    Stack s;
    //Run white box tests
    whiteBoxTests();

    //Run black box tests
    //Black box tests should test the ADT through the interface only
    printf("Black Box tests:\n");
    printf("This is just a small example for you to get started\n");

    printf("Test 1: createStack");
    s = createStack();
    assert(s != NULL);
    assert(stackSize(s) == 0);
    printf("Passed\n");

    printf("Test 2: push to double stack\n");
    int i;
    for ( i = 0; i < 15; ++i ) {
        push( s, i );
    }
    printf("Test 3: double maxSize: %d\n", s->maxSize );
    for ( i = 0; i < 15; ++i ) {
        pop( s );
    }
    printf("Test 4: reduce maxSize: %d\n", s->maxSize );
    destroyStack( s );
    assert( s );
    printf("Test 5: stack destroyed.\n");
          
    //etc

    return 0;
}       
