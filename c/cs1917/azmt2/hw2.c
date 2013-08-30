/* hw2.c

   COMP1917 Computing 1

   Program supplied as a starting point for
   Assignment 2: Message Board

   UNSW Session 2, 2012
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "hw2.h"


int globalMessageNum = 1;

int main( void ) {
	MsgNode *list = NULL;
	MsgNode *node;
	MsgNode *tmpNode;
	MsgNode *tmpNode2;
	MsgNode *initNode;
	char command[MAX_LINE];
	char c;
	int nodeOnCall;
	int listMode = 'p'; // 't'hread, 'p'lain
	int printMode = 'f'; // 'f'ull, 'b'rief

	printPrompt();

	//puts("here we go");

	// enter a loop, reading and executing commands from the user
	while( fgets(command,MAX_LINE,stdin) != NULL ) {
		char *p;

		// replace newline with end-of-string character
		if(( p = strchr(command,'\n')) != NULL ) {
			*p = '\0';
		}
		p = command;
		while( isspace(*p)) { // skip any initial spaces
			p++;
		}
		c = *p;

		if( isdigit(c) ) { // NAV - nth msg

			if( ISDEBUG )
				printf("%c\n",(char)c);	

			nodeOnCall = c - '0'; // (int)c
			list = initNode;
			listAll( list, nodeOnCall, listMode );
			while( list->messageNum != nodeOnCall )
				list = list->next;

		}
		else switch( c ) {

			case 'a': case 'A': // Add item

				if( ISDEBUG )
					printf("%c\n",(char)c);	

				node = getNode();

				if( node->messageNum == 1 ) { // initNode
					initNode = node;
					list     = initNode;
				} else {

					// add to thread list end
					while( list->nextThread != NULL )
						list = list->nextThread;

					list->nextThread = node;
					node->prevThread = list;

					// add to normal list end
					while( list->next != NULL )
						list = list->next;

					list->next = node;
					node->prev = list;

					list = list->next;
				}

				nodeOnCall = node->messageNum;

				if( printMode == 'f' )
					printFull( node );
				else {
					tmpNode = initNode;
					listAll( tmpNode, nodeOnCall, listMode );
				}

				break;

			case 'r': case 'R': // Reply

				if( ISDEBUG )
					printf("%c\n",(char)c);	

				node = getNode();

				node->inReplyTo = nodeOnCall;
				node->indent    = list->indent;
				node->indent++;

				// insert node to thread list
				tmpNode = list->nextThread;
				while( tmpNode->indent > list->indent
					&& tmpNode->nextThread != NULL ) {
					tmpNode = tmpNode->nextThread;
				}

				tmpNode2 = tmpNode;
				tmpNode  = tmpNode->prevThread;

				node->nextThread     = tmpNode2;
				node->prevThread     = tmpNode;

				tmpNode->nextThread  = node;
				tmpNode2->prevThread = node;


				//add to end of list
				while( tmpNode->next != NULL ) {
					tmpNode = tmpNode->next;
				}
				tmpNode->next = node;
				list = node;

				nodeOnCall = node->messageNum;


				if( printMode == 'f' )
					printFull( node );
				else {
					tmpNode = initNode;
					listAll( tmpNode, nodeOnCall, listMode );
				}

				break;

			case 'l': case 'L': case 't': case 'T': // List or Threads

				if( ISDEBUG )
					printf("%c\n",(char)c);	

				listMode = c;
				printMode = 'b'; // brief

				tmpNode = initNode;
				listAll( tmpNode, nodeOnCall, listMode );

				break;

			case 'p': case 'P': // Print

				if( ISDEBUG )
					printf("%c\n",(char)c);	

				printMode = 'f'; // full

				printFull( list );

				break;

			case 'f': case 'F': // NAV - Forward

				if( ISDEBUG ) {
					printf("%c\n",(char)c);	
					puts( list->next == NULL ? "NULL1" : "no" );
					puts( list->nextThread == NULL ? "NULL2" : "no" );
				}

				if( listMode == 'p' && list->next != NULL ) {
					if( ISDEBUG )
						puts("wtf i did it?");
					list = list->next;
					nodeOnCall = list->messageNum;
					if( printMode == 'f' )
						printFull( list );
					else {
						tmpNode = initNode;
						listAll( tmpNode, nodeOnCall, listMode );
					}
				} else if( listMode == 't' && list->nextThread != NULL) {
					if( ISDEBUG )
						puts("wtf i did it?");
					list = list->nextThread;
					nodeOnCall = list->messageNum;
					if( printMode == 'f' )
						printFull( list );
					else {
						tmpNode = initNode;
						listAll( tmpNode, nodeOnCall, listMode );
					}	
				}

				break;

			case 'b': case 'B': // NAV - Back

				if( ISDEBUG ) {
					printf("%c\n",(char)c);	
					puts( list->next == NULL ? "NULL1" : "no" );
					puts( list->nextThread == NULL ? "NULL2" : "no" );
				}

				if( listMode == 'p' && list->prev != NULL ) {
					if( ISDEBUG )
						puts("is this working?");
					list = list->prev;
					nodeOnCall = list->messageNum;
					if( printMode == 'f' )
						printFull( list );
					else {
						tmpNode = initNode;
						listAll( tmpNode, nodeOnCall, listMode );
					}
				} else if( listMode == 't' && list->prevThread != NULL) {
					if( ISDEBUG )
						puts("is this working?");
					list = list->prevThread;
					nodeOnCall = list->messageNum;
					if( printMode == 'f' )
						printFull( list );
					else {
						tmpNode = initNode;
						listAll( tmpNode, nodeOnCall, listMode );
					}	
				}

				break;


			case 'd': case 'D': // Delete

				if( ISDEBUG )
					printf("%c\n",(char)c);	

				list->deleted = 1;
				list          = initNode;
				listAll( list, nodeOnCall, listMode );
				while( list->messageNum != nodeOnCall ) {
					list = list->next;
				}
				break;

			case 's': case 'S': // Search

				if( ISDEBUG )
					printf("%c\n",(char)c);	

				break;

			case 'u': case 'U': // Undo

				if( ISDEBUG )
					printf("%c\n",(char)c);	

				break;

			case 'h': case 'H': // Help

				if( ISDEBUG )
					printf("%c\n",(char)c);	

				printHelp();
				break;

			case 'q': case 'Q': // Quit

				if( ISDEBUG )
					printf("%c\n",(char)c);	

				list = initNode;
				freeList( list );
				printf("Bye!\n");
				return 0;
				break;
		}

		printPrompt();
	}

	return 0;
}

/* listAll **************************************************
   list messages in brief
   */
void listAll( MsgNode * list, int highLight, int listMode ) {

	int i;
	puts(""); // print a blank line

	while( list != NULL ) {
		printf( list->messageNum == highLight ? "->" : "  " );
		printf("%2d ", list->messageNum );
		if( listMode == 't' ) {
			for( i = 0; i < list->indent; i++)
				printf("   ");
		} // spaces for indent

		printBrief( list );

		if( listMode == 'l' )
			list = list->next;
		else
			list = list->nextThread;
	}

	puts("\n");
}

/* printPrompt **********************************************
   Print prompt only if output goes to screen
   */
void printPrompt() {
	if (isatty(fileno(stdin))) {
		printf("Enter command (A,F,B,P,L,D,R,T,S,U,Q, H for Help): ");
	}
}

/* printHelp ************************************************
   Print the list of commands available to the user,
   and a brief summary of what each command does.
   */
void printHelp() {
	puts("");
	puts(" A - Add");
	puts(" L - List");
	puts(" P - Print");
	puts(" F - Forward");
	puts(" B - Back");
	puts("<k>- jump to message k");
	puts(" D - Delete");
	puts(" R - Reply");
	puts(" T - Threads");
	puts(" S - Search");
	puts(" U - Undo");
	puts(" Q - Quit");
	puts(" H - Help");
	puts("");
}

/* getNote **************************************************
   allocate space for a new message and get the
   name, date, time and text from standard input.
   */
MsgNode * getNode( void ) {
	MsgNode * new_node;
	new_node = (MsgNode *)malloc(sizeof(MsgNode));
	if( new_node == NULL ) {
		printf("Error: could not allocate memory.\n");
		exit( 1 );
	}
	new_node->messageNum = globalMessageNum++;
	new_node->inReplyTo  = 0;
	new_node->indent     = 0;
	new_node->deleted    = FALSE;
	new_node->name       = getName();
	getDate( &new_node->date );
	getTime( &new_node->time );
	new_node->text       = getText();
	new_node->next       = NULL;
	new_node->nextThread = NULL;
	new_node->prev       = NULL;
	new_node->prevThread = NULL;

	return( new_node );
}

/* getName **************************************************
   Read one line of text from standard input,
   store it in a string and return a pointer to the string.
   */
char * getName( void ) {
	char buffer[MAX_LINE];
	char *name;
	int length;
	int ch;
	int i;
	// prompt user for input
	printf( "Name: " );
	// skip any intial newline character
	if(( ch = getchar()) == '\n' ) {
		ch = getchar();
	}
	// read text initially into a buffer
	i=0;
	while( i < MAX_LINE && ch != '\n' && ch != EOF ) {
		buffer[i++] = ch;
		ch = getchar();
	}
	// trim of any trailing whitespace
	while( isspace( buffer[i] )) {
		i--;
	}
	// allocate just enough space to store the string
	length = i;
	name = (char *)malloc((length+1)*sizeof(char));
	if( name == NULL ) {
		printf("Error: could not allocate memory.\n");
		exit( 1 );
	}
	// copy text from buffer into new string
	for( i=0; i < length; i++ ) {
		name[i] = buffer[i];
	}
	name[i] = '\0'; // add end-of-string marker
	return( name );
}

/* getText **************************************************
   Read several lines of text from standard input,
   store them in a string and return a pointer to the string.
   */
char * getText( void ) {
	char buffer[MAX_TEXT];
	char *text;
	int length;
	int ch;
	int i;

	printf("Text: ");
	ch = getchar();
	i=0;
	while(( i < MAX_TEXT )&&( ch != EOF )) {
		buffer[i++] = ch;
		ch = getchar();
		// stop when you encounter a dot on a line by itself
		if( i > 1 && ch == '\n' && buffer[i-1] == '.'
				&& buffer[i-2] == '\n' ) {
			ch = EOF;
			i  = i-2; // strip off the dot and newlines
		}
	}
	length = i;
	// allocate just enough space to store the string
	text = (char *)malloc((length+1)*sizeof(char));
	if( text == NULL ) {
		printf("Error: could not allocate memory.\n");
		exit( 1 );
	}
	// copy text from buffer to new string
	for( i=0; i<length; i++ ) {
		text[i] = buffer[i];
	}
	text[i] = '\0'; // add end-of-string marker

	return( text );
}

/* getDate **************************************************
   Get date from standard input;
   if date is invalid, ask the user to re-enter it.
   */
void getDate( Date *d ) {
	printf("Date: ");
	while( !scanDate( d ) || !dateOK( d )) {
		printf("Re-enter date in format dd/mm/yy: ");
	}
}

/* scanDate *************************************************
   scan date in the format dd/mm/yyyy
   */
int scanDate( Date *d ) {
	char s[MAX_LINE];

	fgets( s, MAX_LINE, stdin );
	if(sscanf(s,"%d/%d/%d",&d->day,&d->month,&d->year)<3){
		return FALSE;
	}
	if( d->year < 100 ) { // turn /12 into /2012, etc.
		d->year = 2000 + d->year;
	}
	return TRUE;
}

/* getTime **************************************************
   Get time from standard input;
   if time is invalid, ask the user to re-enter it.
   */
void getTime( Time *t ) {
	printf("Time: ");
	while( !scanTime( t ) || !timeOK( t )) {
		printf("Re-enter time in format hh:mm:ss: ");
	}
}

/* scanTime *************************************************
   scan time in the format hh:mm:ss
   */
int scanTime( Time *t ) {
	char s[MAX_LINE];

	fgets( s, MAX_LINE, stdin );
	return( sscanf(s,"%d:%d:%d",&t->hour,&t->minute,&t->second)==3 );
}

/* dateOK ***************************************************
   Return TRUE if date is valid; FALSE otherwise.
   */
int dateOK( Date *d ) {

	int isLeapYear = FALSE;
	int isDate = ( ( d->day > 0 ) && ( d->day < 32) &&
			( d->month > 0 ) && ( d->month < 13 ) && ( d->year > 1581 ) );

	// leap year, algorithm from wikipedia
	if( (d->year)%400 == 0 )
		isLeapYear = TRUE;
	else if( (d->year)%100 == 0 )
		isLeapYear = FALSE;
	else if( (d->year)%4 == 0)
		isLeapYear = TRUE;
	else
		isLeapYear = FALSE;

	if( isDate ) {
		switch( d->month ) {
			case 2: // Feb.
				isDate = ((isLeapYear && ( d->day < 30 ))
					|| (!isLeapYear && (d->day < 29)));
				break;

			case 4: case 6: case 9: case 11: // 30 days
				isDate = ( d->day < 31 );
				break;

			default:
				isDate = ( d->day < 32 );
		}
	}

	return isDate;
}

/* timeOK ***************************************************
   Return TRUE if time is valid; FALSE otherwise.
   */
int timeOK( Time *t ) {
	return(   t->hour   >= 0 && t->hour   < 24
			&& t->minute >= 0 && t->minute < 60
			&& t->second >= 0 && t->second < 60 );
}

// INSERT NEW FUNCTIONS, AS APPROPRIATE

/* printPadded **********************************************
   Print the specified integer in two digits (prefixed with '0'
   if necessary), followed by the specified character.
   */
void printPadded( int n, char ch ) {
	if( n < 10 ) {
		putchar('0');
	}
	printf("%d%c",n,ch );
}

/* printDate ************************************************
   Print date in the format dd/mm/yyyy
   */
void printDate( Date d ) {
	printPadded( d.day,  '/');
	printPadded( d.month,'/');
	printf("%d ", d.year );
}

/* printTime ************************************************
   Print time in the format hh:mm:ss
   */
void printTime( Time t ) {
	printPadded( t.hour,  ':');
	printPadded( t.minute,':');
	printPadded( t.second,' ');
}

/* printBrief ***********************************************
   Print the Name, followed by the first line of the Text.
   */
void printBrief( MsgNode * msg ) {
	char *text=msg->text;
	int i=0,j=0;
	if( msg->deleted ) {
		printf("[deleted]\n");
	}
	else {
		printf("%s: ", msg->name );
		while( isspace( text[i] )) {
			i++;
		}
		while( j < 40 && text[i+j] != '\0'
				&& text[i+j] != '\n' ) {
			putchar( text[i+j] );
			j++;
		}
		putchar('\n');
	}
}

/* printFull ************************************************
   Print message in Full
   */
void printFull( MsgNode * msg ) {
	puts("");
	if( msg != NULL ) {
		printf("Message %d", msg->messageNum );
		if( msg->deleted ) {
			printf("has been deleted.\n");
		}
		else {
			printf("\nDate: ");
			printDate( msg->date );
			printf("\nTime: ");
			printTime( msg->time );
			printf("\nName: %s\n", msg->name );
			printf("Text: %s\n", msg->text );
		}
	}

	puts("\n");

}

/* freeList *************************************************
   Free all memory occupied by linked list of messages
   */
void freeList( MsgNode *head ) {
	MsgNode *node;
	while( head != NULL ) {
		node = head;
		head = head->next;
		free( node->name );
		free( node->text );
		free( node );
	}
}
