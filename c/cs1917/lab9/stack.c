/*
   stack.c

   Sample program for COMP1917

   Implement an interactive stack.

   Press:

   <Return>  : to print content of stack
   any letter: to push that letter onto stack
     '-'     : to pop top item from stack

   compile like this: gcc -Wall stack.c list.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main( void )
{
   Lnode *list = NULL;
   int  ch;

   while(( ch = getchar()) != EOF ) {
      if( ch == '\n' ) {
	printList( list );
      }
      else if ( ch == '-' ) {
         list = pop( list );
      }
      else {
         list = push( makeNode( ch ), list );
      }
   }
   freeList( list );

   return 0;
}
