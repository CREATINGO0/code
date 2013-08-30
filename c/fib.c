// fibonacci sequence

#include <stdio.h>

int fib( int n );

int main ( void ) {
        int n;
        scanf("%d",&n);
        printf("%d\n",fib(n));

        return 0;
}

int fib( int n ) {
	switch(n){
	case 0: case 1:
		return 1;
		break;
	default:
		return fib(n-1) + fib(n-2);
	}
}
