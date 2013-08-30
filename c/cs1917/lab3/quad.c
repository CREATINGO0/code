#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#define irri _Complex_I

int main(void) {

	double a,b,c,delta;

	printf("Enter the coefficients for a, b and c (Separate with space): ");
	scanf("%lf %lf %lf", &a, &b, &c);

	complex xone,xtwo;

	delta = b*b-4*a*c;
	if ( delta < 0) {
		printf("Delta is %.2f\nNote that delta is smaller than 0.\nThis would give irrational solutions.\n",delta);

		xone = ((0 - b + sqrt( - delta)*irri )/(2*a));
		printf("x_1 is %.2f + %.2fi\n",creal(xone),cimag(xone));

		xtwo = ((0 - b - sqrt( - delta)*irri )/(2*a));
		printf("x_2 is %.2f + %.2fi\n",creal(xtwo),cimag(xtwo));
	}
	else {
		printf("Delta is %.2f\n",delta);

		xone = ((0 - b + sqrt(delta))/(2*a));
		printf("x_1 is %.2f\n",creal(xone));

		xtwo = ((0 - b - sqrt(delta))/(2*a));
		printf("x_2 is %.2f\n",creal(xtwo));

	}

	return 0;
}
