/*
   freq.c

   Sample program for COMP1917
   Print frequencies of letters read from standard input
*/

#include <stdio.h>
#include <ctype.h>

void count_freq( int count[] );
void print_freq( int count[] );

int main( void )
{
  int count[26] = { 0 }; // initialize array elements

  count_freq( count );   // count frequencies
  print_freq( count );   // print frequencies

  return 0;
}

// count the number of occurrences of each letter
void count_freq( int count[] )
{
  int ch;
  int i;

  while(( ch = getchar()) != EOF ) {
    ch = toupper( ch ); // convert to upper case
    if(( ch >= 'A' )&&( ch <= 'Z' )) {
      i = ch - 'A';
      count[i]++;       // increment i'th element
    }
  }
}

void print_freq( int count[] )
{
  double total = 0.0;
  int i;

  // count the total number of letters
  for( i=0; i < 26; i++ ) {
    total += count[i];
  }
  for( i=0; i < 26; i++ ) {
    // print number of occurrences, and percentage of total
    printf( "%c: %5d  [%1.1f",'A'+i,count[i],count[i]*100.0/total);
    putchar('%');
    printf("]\n");
  }
}
