/*
   vigenere.h

   Sample program for COMP1917 Lab 7
*/

#define MAX_KEY 128

extern char key[MAX_KEY];

void encrypt( int ch );
void decrypt( int ch );
