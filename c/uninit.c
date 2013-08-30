#include <stdio.h>

int main( void ){
	int x = 10, y = 3;
	int z = (x%y,x/y);
	printf("%d\n",z);
	return 0;
}
