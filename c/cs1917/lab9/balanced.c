#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main( void ) {
	Lnode *list = NULL;
	int ch,isBalanced = 1;
	while( isBalanced && (( ch = getchar()) != EOF) ) {
		switch( ch ) {
			case ')': case ']': case '}':
				isBalanced = (
						( list != NULL ) &&
						( (list->data == ch - 1) || (list->data == ch - 2) )
						//in ascii: ..()..[\]..{|}..
						);
				list = pop( list );
				break;
			case '(': case '[': case '{':
				list = push( makeNode( ch ), list );
				break;
		}
	}

	puts( (isBalanced && list == NULL) ? "Yes, is balanced" : "No, not balanced");
	freeList( list );
	return 0;
}
