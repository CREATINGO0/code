#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main( void )
{
	Lnode *list = NULL;
	int  ch,isBalanced = 1;

	while( isBalanced && (( ch = getchar()) != EOF) ) {
		switch( ch ) {
			case ')':
				isBalanced = ( list->data == '(' );
				list = pop( list );
				break;

			case ']':
				isBalanced = ( list->data == '[' );
				list = pop( list );
				break;

			case '}':
				isBalanced = ( list->data == '{' );
				list = pop( list );
				break;

			default: list = push( makeNode( ch ), list );
		}
	}

	puts(isBalanced?"Yes, is balanced":"No, not balanced");

	freeList( list );

	return 0;
}
