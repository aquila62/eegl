OBJ=bit2raw.o

CC=gcc

CFLAGS=-c -Wall -O6

LDFLAGS=

bit2raw:			$(OBJ)
		$(CC) -Wall -O6 $(OBJ) -o bit2raw $(LDFLAGS)

bit2raw.o:			bit2raw.c
		$(CC) $(CFLAGS) bit2raw.c

clean:
		rm -f $(OBJ) bit2raw
