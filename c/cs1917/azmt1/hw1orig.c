/**
   Sample code for UNSW COMP1917 Assignment 1

   You are free to copy this code and use it
   as a starting point for your own code.
*/

#include <stdio.h>
#include <math.h>


// YOU MAY INSERT OTHER FUNCTIONS, IF NEEDED

int main( void )
{
  char ch;

  printf("Compute: distance or angle? ");

  scanf("%c",&ch);   // scan first non-space character
  if( ch != '\n' ) { // if necessary, skip to end of line
    while( getchar() != '\n' )
      ;
  }

  if( ch != 'a' && ch != 'A' ) {
    printf("Enter: speed height angle: ");

    // INSERT CODE TO COMPUTE DISTANCE

    printf("no solution\n");
  }
  else {
    printf("Enter: speed height distance: ");

    // INSERT CODE TO COMPUTE ANGLE

    printf("no solution\n");
  }

  return 0;
}
