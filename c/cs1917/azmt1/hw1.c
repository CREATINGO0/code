/*
   Xirui Luo, 3423267
   14/08/2012

   CS1917 12S2 assignment1 - cannonball
 */
#include <stdio.h>
#include <math.h>

float distance(float speed, float height, float theta);
float angle(float speed, float height, float meter);

int main( void ) {
    char  ch;
    float theta, rslt, speed, height, meter;

    printf("Compute: distance or angle? ");

    scanf("%c", &ch);   // scan first non-space character
    if( ch != '\n' ) { // if necessary, skip to end of line
        while( getchar() != '\n' );
    }

    if( ch != 'a' && ch != 'A' ) { //distance
        printf("Enter: speed height angle: ");
        scanf("%f %f %f", &speed, &height, &theta);
        rslt = distance(speed, height, theta);
        if(rslt == 0) {
            printf("no solution\n");
        } else {
            printf("distance is %.2f metres\n", rslt);
        }
    } else { //angle
        printf("Enter: speed height distance: ");
        scanf("%f %f %f", &speed, &height, &meter);
        rslt = angle(speed, height, meter);
        if(rslt ==0) {
            printf("no solution\n");
        } else {
            printf("angle is %.2f degrees\n", rslt);
        }
    }
    return 0;
}

float angle(float v, float h, float d) {
    float x_low, x_hi, x_mid, rslt;
    x_low = atan(v*v/(9.8*d)); //theta lower end, output degrees
    x_hi  = 90; //theta higher end
    x_mid = (x_low + x_hi)/2.0;
    rslt  = distance(v, h, x_mid);
    if(rslt == 0) {
        return 0; //no result
    } else {
        while(fabs(d - rslt) > 0.005) { //abs of float
            rslt = distance(v, h, x_mid);
            if( d > rslt ){ //closer than expected
                x_hi = x_mid;
            } else {
                x_low = x_mid;
            }
            x_mid = (x_low+x_hi)/2.0;
        } //bisection loop end
        return x_mid;
    }
}

float distance(float v, float h, float n) {
    n = n*3.1416/180; //input radians
    if(v*v*sin(n)*sin(n) < 2*9.8*h) {
        return 0; //no result
    } else {
        return v*cos(n)/9.8*(v*sin(n)\
                +sqrt(v*v*sin(n)*sin(n)-19.6*h));
    }
}
