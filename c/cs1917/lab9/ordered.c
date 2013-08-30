/*
   ordered.c

   Sample program for COMP1917

   Implement an interactive ordered linked list.

   Press:
         <Return>  : to print content of stack
         any letter: to insert that letter (in order) to the stack
   '-', then letter: to remove the first item with that letter

   compile like this: gcc -Wall ordered.c list.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main( void )
{
   Lnode *list = NULL;
   Lnode *node;
   int  ch;

   while(( ch = getchar()) != EOF ) {
      if ( ch == '-' ) { // remove item from list
          ch = getchar();
          node = findNode( ch, list );
          if( node != NULL ) {
              list = excise( node, list );
              free( node );
          }
      }
      else if( ch == '\n' ) {
          printList( list );
      }
      else {
          list = insert( makeNode(ch), list );
      }
   }
   freeList( list );

   return 0;
}
