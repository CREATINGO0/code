/*
   list.c

   Sample program for COMP1917

   Provides functions to perform standard list operations,
   as described in lectures.
*/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/*
   Create a new node containing the specified data,
   and return a pointer to this newly-created node.
*/
Lnode * makeNode( int data )
{
   Lnode *new_node =(Lnode *)malloc( sizeof( Lnode ));
   if( new_node == NULL ) {
      fprintf(stderr,"Error: memory allocation failed.\n");
      exit( 1 );
   }
   new_node->data = data;
   new_node->next = NULL;
   return( new_node );
}

/*
   Search through list to find the first node with the
   specified data, and return a pointer to this node.
   If no such node exists, return NULL.
*/
Lnode * findNode( int data, Lnode *head )
{
   Lnode *node = head; // start at first node in list

   // keep searching until data found, or end of list
   while(( node != NULL )&&( node->data != data )) {
      node = node->next;
   }
   return( node );
}

/*
   Push new node to front of list and
   return the resulting (longer) list
*/
Lnode * push( Lnode *new_node, Lnode *head )
{
   new_node->next = head;
   return( new_node );
}

/*
   Pop first item from list and
   return the remaining (shorter) list
*/
Lnode * pop( Lnode *head )
{
    Lnode *tmp;

    if( head != NULL ) {
        tmp  = head;
        head = head->next;
        free( tmp );
    }
    return( head );
}

/*
   Print all items in the list one by one
*/
void printList( Lnode *head )
{
   Lnode *node = head;

   // traverse the list printing each node in turn
   while( node != NULL ) {
       printf( "->%c", node->data );
       node = node->next;
   }
   printf( "\n" );
}

/*
   Delete all the items from a linked list.
*/
void freeList( Lnode *head )
{
   Lnode *node = head;
   Lnode *tmp;

   while( node != NULL ) {
      tmp = node;
      node = node->next;
      free( tmp );
   }
}

Lnode * insert( Lnode *new_node, Lnode *head )
{
   Lnode *next_node = head, *prev_node = NULL;
   while( next_node && new_node->data > next_node->data) {
       prev_node = next_node;
       next_node = next_node->next; // find correct position
   }
   if( prev_node == NULL )
       head = new_node;
   else {
       prev_node->next = new_node;  // link new node into list
   }
   new_node->next = next_node;
   return( head );
}

Lnode * excise( Lnode *node, Lnode *head )
{
   if( node != NULL ) {
       if( node == head )
           head = head->next;         // remove first item
       else {
           Lnode *prev_node = head;
           while( prev_node && prev_node->next != node ) {
               prev_node = prev_node->next;
           }
           if( prev_node != NULL ) { // node found in list
               prev_node->next = node->next;
           }
       }
   }
   return( head );
}

