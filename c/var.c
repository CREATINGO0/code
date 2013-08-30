#include <stdio.h>

int incr( int );

int main( void ) {

	int a = 6;

	int b = incr( a ); 
	printf("incr of %d is %d.\n",a,b);
}

int incr( int x ) {
	x++;
	return x;
}
