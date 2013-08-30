#include <stdio.h>

int main() {
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            printf("(%d,%d) ",i,j);
        }
        puts("");
    }
    return 0;
}
