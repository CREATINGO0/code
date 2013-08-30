# Makefile

CC = gcc
CFLAGS = -Wall

CSRC = cipher.c vigenere.c
HSRC = vigenere.h
OBJ = $(CSRC:.c=.o)

%o:%c $(HSRC)
	$(CC) $(CFLAGS) -c $<


# Additional targets
.PHONY: clean

# Target rules

cipher: $(OBJ)
	$(CC) $(CFLAGS) -o cipher $(OBJ)

clean:
	rm -f $(OBJ)

# Remove obj files and exec files
.PHONY: clobber

clobber:
	rm -f $(OBJ) cipher

.PHONY: test

test:
	./cipher < test.dat
