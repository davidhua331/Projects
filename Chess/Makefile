GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS = `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

INC	= $(GTKINC)
LIBS	= $(GTKLIBS)

OPTS	= -g



all: Chess

CC	= gcc
CFLAGS	= -ansi -Wall -c
LFLAGS	= -Wall
AR	= ar rc
RAN	= ranlib



Piece.o: Piece.c Piece.h Structures.h
	$(CC) $(CFLAGS) Piece.c -o Piece.o

Game.o: Game.c Game.h Structures.h
	$(CC) $(CFLAGS) Game.c -o Game.o

MoveList.o: MoveList.c MoveList.h Structures.h
	$(CC) $(CFLAGS) MoveList.c -o MoveList.o

PossibleMoves.o: PossibleMoves.c PossibleMoves.h Structures.h
	$(CC) $(CFLAGS) PossibleMoves.c -o PossibleMoves.o

Board.o: Board.c Board.h Structures.h
	gcc -c Board.c $(GTKINC) -o Board.o

Chess.o: Chess.c
	$(CC) $(CFLAGS) $(GTKINC) Chess.c -o Chess.o

Chess: Piece.o Game.o MoveList.o PossibleMoves.o Board.o Chess.o 
	$(CC) $(LFLAGS) $(GTKLIBS) Piece.o Game.o MoveList.o PossibleMoves.o Board.o Chess.o -o Chess

clean:
	rm -f Chess *.o