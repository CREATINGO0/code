/*
   cipher.c

   Sample program for COMP1917 Lab 7
 */

#include <stdio.h>

#include "vigenere.h"

char key[MAX_KEY];

int main( void )
{
	int ch;
	char choice = 'a';

	printf("Enter key: ");
	scanf( "%s",  key );

	printf("Encrypt or Decrypt? ");
	while( choice != 'e' && choice != 'd') {
		choice = getchar();
	}


	if( choice == 'e' ) {	//encrypt
		printf("Enter text:\n");
		while(( ch = getchar()) != EOF ) {
			encrypt( ch );
		}
		printf( "\n" );
	} else {	//decrypt
		printf("Enter text:\n");
		while(( ch = getchar()) != EOF ) {
			decrypt( ch );
		}
		printf( "\n" );

	}

	return 0;
}
