#include <stdio.h>
#include <string.h>

void reverse_string( char s[] );

int main( void ) {
	char s[100];

	printf( "Enter string:\n" );
	fgets( s, 100, stdin );

	reverse_string(s);

	printf("%s\n", s );

	return 0;
}

void reverse_string( char s[] ) {

	int i,swap;
	int len = strlen(s);

	for( i = 0; i < len/2; i++ ) {

		swap = s[i];
		s[i] = s[len-i-1];
		s[len-i-1] = swap;
		
	}

}
