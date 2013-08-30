#include <stdio.h>

int main(void) {
	int i,j,sumk;
	sumk = 0;

	printf("   k   sum\n-----------\n");

	for(i=1;i<=20;i++) {
		for(j=1;j<=i;j++){
			sumk += j*j*j;
		} 
		printf("  %2d %5d\n", i, sumk);
		sumk = 0;
	}
	return 0;
}
