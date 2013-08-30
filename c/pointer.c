#include <stdio.h>

int main (void) {
        int a[5] = { 100, 200, 300, 400, 500 };
        int *p = &a[0];

        printf("%d\n", (*p)++);
        printf("%d\n", *(p++));
        printf("%d\n", (*p)++);
        printf("%d\n", *(p++));
        printf("%d\n", (*p)++);
        printf("%d\n", *(p++));
        printf("%d\n", (*p)++);
        printf("%d\n", *(p++));
        printf("%d\n", (*p)++);
        printf("%d\n", *(p++));
        printf("%d\n", (*p)++);
        printf("%d\n", *(p++));
         
        return 0;
}
