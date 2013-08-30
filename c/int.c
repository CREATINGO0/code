#include <stdio.h>

int main( void ){
    float x = 3.1416;
    int y = *(int *)&x;
    printf("%d\n",y);
    return 0;
}
