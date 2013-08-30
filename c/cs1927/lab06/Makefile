#CC = gcc
CC = clang
CFLAGS = -Wall -Werror -g

.PHONY:	clean clobber

all: graphClient

%o:%c
	$(CC) $(CFLAGS) -c $<

graphClient: graphClient.o Graph_AdjMatrix.o
	$(CC) -o graphClient graphClient.o Graph_AdjMatrix.o
clean:
	rm -f *.o core

clobber: clean
	rm -f graphClient
