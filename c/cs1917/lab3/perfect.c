#include <stdio.h>

int main(void) {

	int k;

	for(k=1;k<=10000;k++) {
		if(isPerfect(k)) {
			printf("%d\n",k);
		}
	}
	return 0;
}

int isPerfect(int n) {
	int i,j;
	j = 0;
	for(i=1;i<n;i++) {
		if(n%i==0) {
			j += i;
		}
	}
	if(j == n) {
		return 1;
	}
	else {
		return 0;
	}
}
