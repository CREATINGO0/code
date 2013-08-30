#include <stdio.h>

typedef int *inp;

int main() {
   int i = 3;
   inp a,b,c;
   a = &i;
   b = &i;
   c = &i;
   printf("%d,%d,%d\n",(int)a,(int)b,(int)c);
   printf("%d,%d,%d\n",*a,*b,*c);
   return 0;
}
