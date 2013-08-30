#include <stdio.h>

int main( void ) {
	char str[20];
	puts("input:");
	while( str != "exit" ) {
		fgets( str, 20, stdin);
		printf("%s\n",str);
	}

	return 0;
}
