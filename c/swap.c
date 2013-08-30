#include <stdio.h>

// void swap(int,int);
void swap(int*,int*);

int main( void ){

    int a = 3, b = 5;
    printf("a = %d, b = %d.\n",a,b);

    // swap by using double xor
    // ^ - xor
    /* printf("a = %d, b = %d\n",a,b);

       a = a^b;
       b = b^a;
       a = a^b;
       */

    // swap(a,b);
    swap(&a,&b);
    printf("a = %d, b = %d.\n",a,b);

    return 0;
}

// void swap(int x, int y) {
//     int temp = x;
//     x = y;
//     y = temp;
// }

void swap(int* px, int* py){
    int temp = *px;
    *px = *py;
    *py = temp;
}
