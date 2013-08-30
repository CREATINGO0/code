#include <stdio.h>

int main( void ){
	int a = 3, b = 0;
	printf("a = %d, b = %d\n",a,b);
	b = a++;
	printf("a = %d, b = %d\n",a,b);
	b = ++a;
	printf("a = %d, b = %d\n",a,b);

	return 0;
}
