//An array based implementation of a stack

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Item.h"
#include "Stack.h"
#include "assert.h"

#define DEFAULT_SIZE 10

struct stackImp{
	Item * items; // int
	int top;
	int maxSize;
};

//A stack is created with a default initial size of 10
Stack createStack (void){
	Stack s = malloc(sizeof(struct stackImp)); 
	assert(s != NULL);
	s->items = (Item *)malloc(DEFAULT_SIZE * sizeof(Item));
	assert(s->items != NULL);
	s->top = 0; 
	s->maxSize = DEFAULT_SIZE;
	return s;
}

void destroyStack(Stack stack){
	assert(stack != NULL);
	free(stack->items);
	free(stack);
}

//You need to modify this
void push (Stack stack, Item item){ 
	if( stack->top == stack->maxSize ){
		stack->items = (Item *)realloc( stack->items, 2*stack->maxSize*sizeof( stack->items ));
		stack->maxSize *= 2;
	}

	assert(stack != NULL);
	stack->items[stack->top] = item;
	stack->top++;

}

//You need to modify this
Item pop (Stack stack){ 
	if ( stack == NULL ) {
		puts("stack underflow");
		abort();
	}

	if ( stack->maxSize > DEFAULT_SIZE && stack->top < stack->maxSize/4 ){
		stack->items = (Item *)realloc( stack->items, stack->maxSize*sizeof( stack->items )/2 );
		stack->maxSize /= 2;
	}

	assert(stack != NULL);
	stack->top--;
	return stack->items[stack->top];
}

int stackSize(Stack stack){
	assert(stack != NULL);
	return stack->top;
}

//You need to write these
void whiteBoxTests(void){
	printf("White box tests: not done yet\n");

}