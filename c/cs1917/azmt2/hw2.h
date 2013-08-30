/* hw2.h

   COMP1917 Computing 1

   Program supplied as a starting
   point for Assignment 2:
   Message Board

   UNSW Session 2, 2012
   */

#define TRUE           1
#define FALSE          0

#define MAX_LINE     256
#define MAX_TEXT    4096

#define ISDEBUG        1

typedef struct date    Date;
typedef struct time    Time;
typedef struct msgNode MsgNode;

struct date {
	int day;
	int month;
	int year;
};

struct time {
	int hour;
	int minute;
	int second;
};

struct msgNode {
	int   messageNum;
	int   threadNum;
	int   inReplyTo;
	int   indent;
	int   deleted;
	char *name;
	Date  date;
	Time  time;
	char *text;
	MsgNode *next;
  MsgNode *nextThread;
  MsgNode *prev;
  MsgNode *prevThread;
};

// INSERT NEW FUNCTION
// PROTOTYPES, AS APPROPRIATE

void printPrompt( void );
void   printHelp( void );
MsgNode *getNode( void );
char    *getName( void );
char    *getText( void );
void     getDate( Date * );
int     scanDate( Date * );
void     getTime( Time * );
int     scanTime( Time * );
int       dateOK( Date * );
int       timeOK( Time * );
void printPadded( int , char );
void   printDate( Date );
void   printTime( Time );
void  printBrief( MsgNode * );
void   printFull( MsgNode * );
void    freeList( MsgNode * );
void     listAll( MsgNode *, int, int );
int  searchMatch( MsgNode * ); 

// all commands: a,l,p,f,b,d,r,t,s,u,q,h
