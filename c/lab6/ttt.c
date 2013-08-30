#include <stdio.h>

#define TRUE     1
#define FALSE    0

#define SIZE     3
#define NONE    -1
#define NOUGHTS  0
#define CROSSES  1
#define EMPTY    2

void  scanBoard( int board[SIZE][SIZE] );
void printBoard( int board[SIZE][SIZE] );
int   getWinner( int board[SIZE][SIZE] );

int main( void ) {
    int board[SIZE][SIZE];
    int winner;

    printf("Please enter the board:\n");
    scanBoard( board );

    printf("Here is the board:\n");
    printBoard( board );

    winner = getWinner( board );
    if( winner == NOUGHTS ) {
        printf("\nNoughts win\n");
    } else if( winner == CROSSES ) {
        printf("\nCrosses win\n");
    } else {
        printf("\nThere is no winner\n");
    }
    return 0;
}

void  scanBoard( int board[SIZE][SIZE] ) {
    int i,j;
    for(i=0;i<SIZE;i++) {
        for(j=0;j<SIZE;j++) {
            scanf("%d",&board[i][j]);
        }
    }
}

void printBoard( int board[SIZE][SIZE] ) {
    int i,j;
    for(i=0;i<SIZE;i++) {
        for(j=0;j<SIZE;j++) {
            if(board[i][j] == NOUGHTS) {
                printf("O ");
            } else if(board[i][j] == CROSSES) {
                printf("X ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int getWinner( int board[SIZE][SIZE] ) {
    int i, j;
    int isEnd = 0;
    int winner = NONE;
    
    i = j = 0;

    while( isEnd == 0 && i < SIZE ) {
        while( board[i][j] == board[i][j + 1] ) {
            if( j == SIZE - 2 ) {
                isEnd = 1;
                winner = board[i][j];
                break;
            }
            j++;
        }
        i++;
        j = 0;
    }

    while( isEnd == 0 && j < SIZE ) {
        while( board[i][j] == board[i + 1][j] ) {
            if( i == SIZE - 2 ) {
                isEnd = 1;
                winner = board[i][j];
                break;
            }
            i++;
        }
        j++;
        i = 0;
    }

    while( isEnd == 0 \
            && i < SIZE \
            && (board[i][i] == board[i + 1][i + 1] \
                || board[i][SIZE - i - 1] == board[i + 1][SIZE - 2 - i]) ) {
        if(i == SIZE - 2 ) {
            isEnd = 1;
            winner = board[i][i];
        }
        i++;
    }

    return winner;
}