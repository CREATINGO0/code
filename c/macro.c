#include <stdio.h>

#define isBase2(a) a&a-1

int main( void ){
	int i;
	for( i = 0; i<10; i++ )
		printf("a = %d, %d\n",i,isBase2(i));
	return 0;
}
