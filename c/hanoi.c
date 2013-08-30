#include <stdio.h>

void hanoi( int, int, int, int );

int main( void ){
	int a = 12, b = 11, c = 10;
	hanoi( a+b+c, a, b, c );

	return 0;
}
	

void hanoi(int n, int A, int B, int C) {
	if( n > 0 ) {
		hanoi(n-1,A,C,B);
		printf("move %d from %d to %d",n,A,C);
		hanoi(n-1,B,A,C);
	}
}
