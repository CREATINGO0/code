#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char *p;
	p = (char *)malloc(20*sizeof(char));
	if( p == NULL ) abort();

	free((void *)p);

	return 0;
}
