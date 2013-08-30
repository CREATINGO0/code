// odd 1s or even in bin

#include <stdio.h>

int main( void ){
	int a = 13114521;

	a = a ^ ( a >> 1 );
	a = a ^ ( a >> 2 );
	a = a ^ ( a >> 4 );
	a = a ^ ( a >> 8 );
	a = a ^ ( a >> 16 );


	puts( a & 1 ? "odd" : "even" );

	return 0;
}
