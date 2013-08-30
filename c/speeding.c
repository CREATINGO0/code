/** \file speeding.c

   Sample Program for COMP1917

   Read a list of driving licences from one file
   and a list of speeding incidents from another file;
   then print an infringement notice for each speeding incident.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LICENCE  300
#define MAX_SPEEDING 500
#define MAX_PLATE     10
#define MAX_NAME      20

typedef struct date     Date;
typedef struct time     Time;
typedef struct licence  Licence;
typedef struct speeding Speeding;

struct date { int day, month, year; };
struct time { int hour, minute; };

struct licence {
  char   plate[MAX_PLATE];
  char   name[MAX_NAME];
};

struct speeding {
  Date   date;
  Time   time;
  double speed;
  char   plate[MAX_PLATE];
};

int scan_date( Date *d, FILE *fp );
int scan_time( Time *t, FILE *fp );

Licence  * scan_licence( FILE *fp );
Speeding * scan_speeding( FILE *fp );

void print_date( Date date );
void print_time( Time time );

void print_notices(
                    Speeding *spd[],
                    Licence  *lnc[]
                  );

/**
   Read a list of driving licences from one file
   and a list of speeding incidents from another file;
   then print an infringement notice for each speeding incident.
*/
int main( int argc, char *argv[] ) {

  FILE *lfile; // licence  file
  FILE *sfile; // speeding file
  int l,s;

  Licence  *licence[MAX_LICENCE+1];  // array of licences
  Speeding *speeding[MAX_SPEEDING+1];// array of speeding incidents

  Licence  *this_licence;
  Speeding *this_speeding;

  if( argc < 3 ) {
    printf("Usage: %s <licence_file> <incident_file>\n",argv[0]);
    exit( 1 );
  }

  // open file to read licences
  lfile = fopen( argv[1], "r" );
  l = 0;
  this_licence = scan_licence( lfile );
  while(( l < MAX_LICENCE )&&( this_licence != NULL )) {
    // keep scanning while there are still licences to read
    licence[l++] = this_licence;
    this_licence = scan_licence( lfile );
  }
  // use NULL to signal that there are no more licences
  licence[l] = NULL;
  fclose( lfile );

  // open file to read speeding incidents
  sfile = fopen( argv[2], "r" );
  s = 0;
  this_speeding = scan_speeding( sfile );
  while(( s < MAX_SPEEDING )&&( this_speeding != NULL )) {
    // keep scanning while there are still speeding incidents
    speeding[s++] = this_speeding;
    this_speeding = scan_speeding( sfile );
  }
  // use NULL to signal that there are no more speeding incidents
  speeding[s] = NULL;
  fclose( sfile );

  // print an infringement notice for each speeding incident
  print_notices( speeding, licence );

  // free the memory that was used
  for( l=0; licence[l] != NULL; l++ ) {
    free( licence[l] );
  }
  for( s=0; speeding[s] != NULL; s++ ) {
    free( speeding[s] );
  }

  return 0;
}

/**
   Create a new Licence and scan the relevant details
   from the file pointer fp, in this format:
<pre>
John Smith
 JJJ 472
Mary Brown
 ABC 123
</pre>
   @param  fp file pointer to read from
   @return pointer to newly created licence
*/
Licence * scan_licence( FILE *fp )
{
  Licence * new_licence = (Licence *)malloc(sizeof(Licence));

  if( new_licence != NULL ) {
    if(  ( fgets( new_licence->name,  MAX_NAME,  fp ))
       &&( fgets( new_licence->plate, MAX_PLATE, fp ))) {
      return( new_licence );
    }
    else {
      // if the information cannot be read, free the space
      free( new_licence );
    }
  }
  // if malloc() or fgets() fail, return NULL
  return( NULL );
}

/**
   Scan a date from the file pointer fp,
   in the format day/month/year

  @param  d pointer to the Date to be scanned
  @param fp file pointer to read from
  @return 1 if successful, 0 otherwise
*/
int scan_date( Date *d, FILE *fp )
{
  return
    (fscanf(fp,"%d/%d/%d",&d->day,&d->month,&d->year)==3);
}

/**
   Scan a time from the file pointer fp,
   in the format hour:minute

  @param  d pointer to the Time to be scanned
  @param fp file pointer to read from
  @return 1 if successful, 0 otherwise
*/
int scan_time( Time *t, FILE *fp )
{
  return
    ( fscanf( fp,"%d:%d", &t->hour, &t->minute ) == 2 );
}

/**
   Create a record of a speeding incident
   and scan the relevant data from the file pointer fp,
   in this format:

   2/3/2005 3:45 87.6 JJJ 472

   @param  fp file pointer to read from
   @return pointer to newly created speeding incident
*/
Speeding * scan_speeding( FILE *fp )
{
  Speeding * new_speeding = (Speeding *)malloc(sizeof(Speeding));

  if( new_speeding != NULL ) {
    if(  ( scan_date( &new_speeding->date, fp ))
       &&( scan_time( &new_speeding->time, fp ))
       && fscanf( fp,"%lf", &new_speeding->speed )
       && fgets( new_speeding->plate, MAX_PLATE, fp )) {
      return( new_speeding );
    }
    else {
      free( new_speeding );
    }
  }

  return( NULL );
}

/**
   Print a date in the format
   day/month/year

   @param date to be printed
*/
void print_date( Date date )
{
  printf( "%d/%d/%d", date.day, date.month, date.year );
}

/**
   Print the specified time in the format
   hour:minute

   @param time to be printed
*/
void print_time( Time time )
{
  printf( "%d:%d", time.hour, time.minute );
}

/**
   Print an infringement notice for each speeding incident,
   in this format:
<pre>
John Smith,
on 2/3/2005, at 3:45,
you were found traveling at 87.6 km/h
</pre>
   @param spd[] array of speeding incidents
   @param lnc[] array of licences
*/
void print_notices(
                    Speeding *spd[],
                    Licence  *lnc[]
                  )
{
  int l,s;

  // for each speeding captured by the camera

  for( s=0; spd[s] != NULL; s++ ) {

    // search all known licences to find matching plate
    for( l=0; lnc[l] != NULL; l++ ) {
      if( strcmp( lnc[l]->plate, spd[s]->plate ) == 0 ) {

        // print infringement notice
        printf( "\n%s", lnc[l]->name );
        printf( "On " );
        print_date( spd[s]->date );
        printf( " at " );
        print_time( spd[s]->time );
        printf("\nyou were found traveling at %1.1f km/h\n",
                    spd[s]->speed);
      }
    }
  }
}

