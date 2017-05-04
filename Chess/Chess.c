#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Structures.h"
#include "Board.h"

void PrintBoard(GAME *game);
void PrintPossibleMoves(LPMOVES *list);
int CheckPossibleMoves(LPMOVES *list, int x, int y);
int Checkmate(GAME *game, color Color);
void DrawBoard(GAME *game);
enum GRID Background[8][8];

int main(int argc, char *argv[]) {
	GAME *game;
	PIECE *piece;
	int x_coord, y_coord;
	color current;
	gtk_init(&argc, &argv);

	game = CreateGame();
	current = white;
	PrintBoard(game);


Display(argc, argv, game); 

	while(Checkmate(game, current)) {
		printf("The current color is ");
		switch(current) {
			case white:	printf("white.\n");
					break;
			default:	printf("black.\n");
		}
		printf("Please type the coordinates for your unit.\n");
		scanf("%d,%d", &x_coord, &y_coord);
		while(!game -> Board[x_coord][y_coord] || (game -> Board[x_coord][y_coord] -> value != current)) {
			printf("Invalid selection. Please try again\n");
			printf("Please type the coordinates for your unit.\n");
			scanf("%d, %d", &x_coord, &y_coord);
		}
		piece = game -> Board[x_coord][y_coord];

		printf("Your available positions for this unit are:\n");
		game -> PossibleMoves = FindPossibleMoves(game, piece);
		PrintPossibleMoves(game -> PossibleMoves);
		printf("Please select where you would like to move the unit: \n");
		scanf("%d,%d", &x_coord, &y_coord);
		while(!CheckPossibleMoves(game -> PossibleMoves, x_coord, y_coord)) {
			printf("Those coordinates are unavailable\n");
			printf("Your available positions for this unit are:\n");
			PrintPossibleMoves(game -> PossibleMoves);
			printf("Please select where you would like to move the unit: \n");
			scanf("%d,%d", &x_coord, &y_coord);
		}
		move(game, piece -> x_coord, piece -> y_coord, x_coord, y_coord);
		PrintBoard(game);
		
		current = (current == white) ? black : white;

	}


	/* int test;
	MOVE *test1;
	printf("Undoing. Acknowledge: ");
	scanf("%d", &test);
	Undo(game -> Board, game -> List);
	PrintBoard(game); */

	printf("Checkmate\n");



	DeleteGame(game);

	return 0;
}

void PrintBoard(GAME *game) 
{
	PIECE *piece;
	int i, j;
	char c, t;
	printf(" +--+--+--+--+--+--+--+--+\n");
	for (j = 7; j>=0;j--)
	{		
		printf("%d|",j);
		for(i = 0; i < 8;i++)
		{
			piece = game->Board[i][j];
			if(piece == NULL)
			{
				printf("  |");
			}
			else
			{
				if(piece ->value == black)
				{ 
					c = 'B';
				}
				if(piece->value == white){
					c = 'W';
				}
				if(piece -> type == king)
				{t = 'k';}
				if(piece ->type == queen)
				{t = 'q';}
				if(piece ->type == bishop)
				{t = 'b';}
				if(piece ->type==knight)
				{t= 'n';}
				if(piece->type==rook)
				{t = 'r';}
				if(piece->type ==pawn)
				{t = 'p';}
				printf("%c%c|", c,t);
			}
		}
	printf("\n +--+--+--+--+--+--+--+--+\n");
	}
	printf("  0  1  2  3  4  5  6  7  \n");
}

void PrintPossibleMoves(LPMOVES *list) {
	PMOVE *move;
	int i;

	assert(list);

	move = list -> First;
	for(i = 0; i < list -> Length; i++) {
		printf("(%d, %d) ", move -> x, move -> y);
		move = move -> Next;
	}
	printf("\n");
}

int CheckPossibleMoves(LPMOVES *list, int x, int y) {
	PMOVE *move;
	int i;
	move = list -> First;

	for(i = 0; i < list -> Length; i++) {
		if(x == move -> x && y == move -> y)
			return 1;
		move = move -> Next;
	}
	return 0;
}

int Checkmate(GAME *game, color Color){
	int x, y;
	
	for (x=0; x<8; x++)
		for (y=0; y<8; y++){
			if (game -> Board[x][y] && game->Board[x][y]->value == Color){ /* whether color of that piece matches*/				
				game -> PossibleMoves = FindPossibleMoves(game, game->Board[x][y]);
				if (game -> PossibleMoves -> Length){
					return 1;
				}
			}
		}
	return 0;
}

int CheckInput(char str[]) {
	int i, position;
	int coordinates[2];;

	position = 0;

	if(str[0] == 'z' || str[0] == 'Z')
		return 1;

	else
		for(i = 0; i < 10; i++) {
			if(position == 2)
				break;
			else if(str[i] >= '0' && str[i] < '8') {
				coordinates[position] = str[i];
				position++;
			}
		}
	if(position == 2)
		return 2;

	return 0;

}


