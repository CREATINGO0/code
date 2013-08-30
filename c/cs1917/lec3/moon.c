#include <stdio.h>

int main (void) {

	double radius = 20;
	int r, c;

	for( r = -20 ; r <= 20 ; r++) {
		for( c = -20 ; c <= 20 ; c++) {
			if( r * r + c * c < radius * radius) {
				printf(".");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}
