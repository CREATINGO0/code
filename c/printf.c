#include <stdio.h>

int main(void){
    int n = 0;

    int i;

    puts("good?");

    for(i=0;i<10;i++){
        n = printf("%d\n",n);
    }

    puts("good!");

    return 0;
}
