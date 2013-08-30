// print ascii of each letter

#include <stdio.h>

int main(void) {
        char *p = "this is it";
        

        while(*p != '\0') {
                printf("%d\n",*p);
                p++;
        }

        return 0;
}
