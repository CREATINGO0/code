#include <stdio.h>

int main( void ) {
	int x, y, z,counter = 0;

	for(x = 0; x < 3; x++){
		for(y = 0; y < 3; y++){
			for(z = 0; z < 3; z++){
				printf("%2d.",counter++);
				puts(((x<=y)&&(y<=z)) == ((x<=y)&(y<=z))?"same":"diff");
			}
		}
	}

	return 0;
}
