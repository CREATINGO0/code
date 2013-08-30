#include <stdio.h>

int main (void) {
	float x_large,x_small,x_mid;
	scanf("%f %f",&x_large,x_small);
	while(x_large > x_small) {
		x_mid = (x_large + x_small) /2;
		
