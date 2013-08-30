/* textbuffer.c
 * CS1927 13x1 assn1
 * z3423267, chad luo
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "textbuffer.h"

#ifndef MAX_LINE
#define MAX_LINE 256
#define DEBUG 1

// printf(DEBUG?"debug flag":"");

typedef struct lineString *LS;
struct lineString {

	char *content;
	LS next;	

};

struct textbuffer{
	LS first,line;
};

TB newTB (char text[]){
	/* allocates a new textbuffer
	 * initialises its contents with the text given in the array
	 * lines in the input array are all terminated by a '\n'
	 * whole text is terminated by a '\0'.
	 */

	TB newtb = (TB)malloc(sizeof(TB));
	newtb->first = NULL;
	newtb->line  = NULL;
	if(DEBUG)
		puts("TB inited");

	int txtIdx = 0, bufIdx = 0, i = 0;
	char buffer[MAX_LINE];

	while( text[txtIdx] != '\0' ){

		if( text[txtIdx] == '\n' ){ // new line

			if(DEBUG)
				puts("new line flag");

			// alloc new line
			char *line;
			// +3: start at 0, \n and \0
			line = (char *)malloc((bufIdx+3)*sizeof(char));
			if( !line ) abort();
			if(DEBUG) puts("line malloced");

			// copy buffer to new line
			for( i = 0; i <= bufIdx; i++ )
				line[i] = buffer[i];
			line[i++] = '\n';
			line[i++] = '\0';
			if(DEBUG){
				printf("new line: %s\n", line );
			}

			// link line and tb
			LS string = (LS)malloc(sizeof(LS));
			string->content = line;
			string->next = NULL;
			if( !newtb->line )
				newtb->line = string;
			else {
				newtb->line->next = string;
				newtb->line = string;
			}
			if( !newtb->first )
				newtb->first = string;
			if(DEBUG)
				puts("linked");

			bufIdx = 0;
		} else { // copy
			buffer[bufIdx] = text[txtIdx];
			bufIdx++;
			if(DEBUG)
				printf("copied: %c\n",buffer[bufIdx]);
		}
		txtIdx++;
	}

	if(DEBUG)
		puts("newTB works");
	return newtb;

}

void releaseTB (TB tb){
	/* frees the memory occupied by the given textbuffer
	 * error to access a buffer after freeing it.
	 */

	tb->line = tb->first;
	LS handle = NULL;

	while( tb->line != NULL ){
		handle = tb->line;
		tb->line = tb->line->next;
		handle->next = NULL;
		free(handle->content);
		free(handle->next);
		free(handle);
		tb->first = tb->line;
	}

	free(tb);

	if(DEBUG) puts("tb freed");

}

// Early Bird
char *dumpTB (TB tb){

	/* do not alter their textbuffer argument
	 * allocate and return an array containing the text in the given textbuffer
	 * each line of the textbuffer terminated by a '\n'
	 * whole text '\0' terminated
	 * caller's responsibility to free the memory occupied by the returned array
	 * if there are no lines in the textbuffer, return NULL.
	 */

	tb->line = tb->first;
	char *text = (char*)malloc(sizeof(char));
	// char *text = (char*)malloc(linesTB(tb)*MAX_LINE*sizeof(char));
	if( !text ) abort();

	while( tb->line != NULL ){
		strcat(text, tb->line->content);
		strcat(text, "\n");
		tb->line = tb->line->next;
		if(DEBUG)
			puts("line appended");
	}

	if(DEBUG)
		puts("dumpTB works");

	return text;

}

int linesTB (TB tb){
	// return the number of lines of the given textbuffer.

	int lineNum = 0;
	tb->line = tb->first;
	while( tb->line != NULL ){
		lineNum++;
		tb->line = tb->line->next;
	}

	return lineNum;

}

// Early Bird
void swapTB (TB tb, int pos1, int pos2){
	/* if line number out of range:
	 *     print a suitable error message
	 *     terminate the program with abort()
	 * first line of a textbuffer is at position 0
	 * swap the two given lines in the textbuffer
	 */
	if(DEBUG)
		puts("swap begins");

	if( pos1 < 0 || pos1 > linesTB(tb) || pos2 < 0 || pos2 > linesTB(tb) ){
		printf("Number out of range.");
		abort();
	}

	tb->line = tb->first;
	int lineIndex = 0;
	LS tempLS1 = NULL, tempLS2 = NULL, tempLS = (LS)malloc(sizeof(LS));

	while( tb->line ){

		if(lineIndex == pos1) tempLS1 = tb->line;
		if(lineIndex == pos2) tempLS2 = tb->line;

		tb->line = tb->line->next;
		lineIndex++;
	}

	if(DEBUG) printf("%s, %s",tempLS1->content,tempLS2->content);

	// swap content instead of LS
	tempLS  = tempLS2;
	tempLS2 = tempLS1;
	tempLS1 = tempLS;
}



void mergeTB (TB tb1, int pos, TB tb2){
	/* line0 of tb2 will be line pos of tb1. 
	 * old line pos of tb1 will follow after the last line of tb2
	 * tb2 can not be used anymore (as if we had used releaseTB() on it).
	 */

	if( pos > linesTB(tb1) || pos < 0 || tb1 == tb2 ) abort();

	// init
	int index = 1;
	tb2->line = tb2->first;

	// reach break pos and set both end flags
	while( index < pos ){
		tb1->line = tb1->line->next;
		index++;
	}

	LS cutfront = tb1->line; // front flag
	LS cutback  = cutfront->next; // back flag

	// link front flag
	cutfront    = tb2->first;

	// link back flag
	while( tb2->line->next != NULL )
		tb2->line = tb2->line->next;
	tb2->line->next = cutback;
}

void pasteTB (TB tb1, int pos, TB tb2){
	/* Like mergeTB()
	 * tb2 remains unmodified and is still usable independent of tb1.
	 */
	TB tb3 = copyTB(tb2, 0, linesTB(tb2));
	mergeTB(tb1, pos, tb3);
}

TB cutTB (TB tb, int from, int to){
	// For all extracting functions, if any
	// of the arguments indicating a line number
	// is out of range, the function has to print
	// a suitable error message and terminate the
	// program with the standard function abort().
	// The textbuffers returned by the extracting
	// functions are as newly created with newTB().
	// Cut the lines between and including from and
	// to out of the textbuffer tb. The cut lines
	// will be deleted from tb. If to is less than
	// from, return NULL.

	if( from < 0 || to < 0 || from > linesTB(tb) || to > linesTB(tb)
			|| from > to )
		return NULL;
	else {

		int i;
		tb->line = tb->first;
		TB cutbuffer = (TB)malloc(sizeof(TB));

		// reach 'from'-1 pos
		for( i = 0; i < from -1; i++ ){
			tb->line = tb->line->next;
		}
		return cutbuffer;
	}
}


TB copyTB (TB tb, int from, int to){
	// textbuffer tb remains unmodified
	// If to is less than from, return NULL.
	int i = from;

	if( from < 0 || to < 0 || from > linesTB(tb) || to > linesTB(tb)
			|| from > to )
		return NULL;
	else {
		// init TB
		TB copiedTB = (TB)malloc(sizeof(TB));
		copiedTB->first = NULL;
		copiedTB->line = NULL;


		// init LS
		LS first = NULL;
		LS link  = first;
		copiedTB->first = first;
		copiedTB->line  = link;

		// copy and connect LS
		while( i <= to ){
			LS line = (LS)malloc(sizeof(tb->line));
			line->content = strcpy(line->content,tb->line->content);
			if( !first ) first = line;
			link->next = line;
			link = line;
			tb->line = tb->line->next;
			i++;
		}
		return copiedTB;
	}
}

// Early Bird
void deleteTB (TB tb, int from, int to){
	if( from < 0 || to < 0 || from > linesTB(tb) || to > linesTB(tb)
			|| from > to )
		abort();
	else {
		int i;
		tb->line = tb->first;

		// reach 'from'-1 pos
		for( i = 0; i < from -1; i++ ){
			tb->line = tb->line->next;
		}
		LS flag = tb->line;
		tb->line = tb->line->next;

		// free from 'from' to 'to'
		while( i < to ){
			tb->line = tb->line->next;
			free( flag->next );
			flag->next = tb->line;
			i++;
		}

		// connect
		flag->next = tb->line;
	}
}

// Early Bird
void replaceText (TB tb, char* str1, char* str2){
	/* searches every line of tb
	 * each str1 and replaces them with str2.
	 */
	int lenold = strlen(str1), lennew = strlen(str2);
	int occr,step;
	char *ins;
	ins = strstr(tb->line->content,str1);

	while(tb->line){
		char *tmp;
		tmp = malloc(sizeof(tb->line->content) + (lennew - lenold)*occr);
		for (occr = 0; (tmp = strstr(ins, str1)) != NULL; ++occr) ins = tmp + lenold;
		while(occr--){
			ins = strstr(tb->line->content,str1);
			step = ins - tb->line->content;
			tmp = strncpy(tmp, tb->line->content, step) + step;
        	tmp = strcpy(tmp, str2) + lennew;
        	tb->line->content += step + lenold;
		}
		free(tb->line->content);
		tb->line->content = tmp;
		tb->line = tb->line->next;
	}
}

// Bonus


char* diffTB (TB tb1, TB tb2){
	return NULL;

}

void undoTB (TB tb){

}

void redoTB (TB tb){

}

#endif
