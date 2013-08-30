#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int isPalindrome( char s[] );

int main( void ) {
        char s[100];

        fgets( s, 100, stdin );

        if( isPalindrome(s) ) {
                printf( "Yes, is a palindrome.\n" );
        } else {
                printf( "No, not a palindrome.\n" );
        }

        return 0;
}

int isPalindrome( char s[] ) {

        int s_lo,s_hi,isEnd,isPld;
        s_lo = 0;
        s_hi = strlen(s);
        isEnd = 0;
        isPld = 0;

//        while( s[s_lo] != '\0' ) {
//                s[s_lo] = toupper(s[s_lo]);
//                s_lo++;
//        }       //uppercase all 4 comparing

        s_lo = 0;

        while( isEnd == 0 && s_lo < s_hi ) {

                while( !isalpha( s[s_lo] ))
                        s_lo++;

                while( !isalpha( s[s_hi] ))
                        s_hi--;

                if( toupper(s[s_lo]) !=  toupper(s[s_hi]) ) {
                        isEnd = 1; isPld = 0;
                } else {
                        isEnd = 0; isPld = 1;
                }

                s_lo++; s_hi--;

        }

        return isPld;
}
