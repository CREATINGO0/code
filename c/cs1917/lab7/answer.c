#include <stdio.h>
#include <ctype.h>

int isPalindrome( char *s );

int main( void )
{
  char s[100];

  printf( "Enter string:\n" );
  fgets( s, 100, stdin );

  if( isPalindrome( s )) {
    printf( "Yes, is a palindrome.\n" );
  }
  else {
    printf( "No, not a palindrome.\n" );
  }

  return 0;
}

int isPalindrome( char *s )
{
  int len;
  int lo, hi;

  // find length of string
  for( len=0; s[len] != '\0'; len++ )
    ;

  // scan simultaneously from the front and back,
  // comparing characters as you go.
  lo = 0;
  hi = len-1;

  while( hi > lo ) {
    // scan backwards to next alphabetic character
    while( hi > lo && !isalpha( s[hi] )) {
      hi--;
    }
    // scan  forwards to next alphabetic character
    while( lo < hi && !isalpha( s[lo] )) {
      lo++;
    }
    // if characters are not equal, return 0
    if( toupper( s[hi] ) != toupper( s[lo] )) {
      return 0;
    }
    lo++; // move to next character
    hi--; // move to previous character
  }

  // if no difference found, return 1
  return 1;
}

