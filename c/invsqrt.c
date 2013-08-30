#include <stdio.h>

float invSqrt(float);

int main( void ){
    float x;
    do{
        printf("x:");
        scanf("%f",&x);
        float y = invSqrt(x);
        printf("inverse sqrt is %f\n",y);
    } while(x != 0.0);
    return 0;
}

float invSqrt(float x) {
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f-xhalf*x*x);
    return x;
}
