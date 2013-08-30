#include <stdio.h>

int main(void) {
        float x = 0.0;
        int y = 0;

        while(x<1.0) {
                x = x+0.02;
                printf("%d\t%f\n",y,x);
                y++;
        }
}
