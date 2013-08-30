#include <stdio.h>
#include <math.h>

int main(void) {
	double a, b, c;
	double s;
	double area;

	printf("load the length of the sides.\n");
	scanf("%lf %lf %lf", &a, &b, &c);

	if ((a < (b + c))&&(b < (a + c))&&(c < (a + b))) {
		s = ( a + b + c ) / 2.0;
		area = sqrt( s * ( s - a ) * ( s - b ) * ( s - c ) );
		printf("area is %lf\n", area);
	}
	else {
		printf("not a triangle.\n");
	}

	return 0;
}
