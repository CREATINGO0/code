#include <stdio.h>

int main(void) {
        float x = 22 / 7;

        printf( "%1.2f\n", x );
        printf( "%1.2f\n", 22 / 7.0 );
        printf( "%1.2f\n", (float) 22 / 7 );
        printf( "%1.2f\n", (float) ( 22 / 7 ) );
        printf( "%1.2f\n", 22 / 7 );
        return 0;
}
