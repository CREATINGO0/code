/*
   list.h

   Sample program for COMP1917

   Header file for list.c
*/

typedef struct lnode Lnode;

struct lnode {
  int    data;
  Lnode *next;
};

Lnode * makeNode( int data );    // create new node
Lnode * findNode( int data, Lnode *head );

Lnode * push( Lnode *new_node, Lnode *head );// to front
Lnode * pop ( Lnode *head );                 // first item

void    printList( Lnode *head ); // print all items
void    freeList ( Lnode *head ); // clear entire list

Lnode * insert( Lnode *new_node, Lnode *head );// in order
Lnode * excise( Lnode *old_node, Lnode *head );
