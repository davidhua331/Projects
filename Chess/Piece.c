#include "Piece.h"

PIECE *CreatePiece(color shade, unit_type unit, unsigned int x, unsigned int y) 
{
	PIECE *piece;
	piece = malloc(sizeof(PIECE));
	piece->x_coord = x;
	piece->y_coord = y;
	piece->value = shade;
	piece->type = unit;
	return piece;
}

void DeletePiece(PIECE *piece)
{
	assert(piece);
	free(piece);
}

/* void DeletePiece(GAME *game, unsigned int x, unsigned int y)
{
	assert(game->Board[x][y]);
	PIECE *piece = game->Board[x][y];
	game->Board[x][y]=NULL; 	
	free(piece);
} */

void move(GAME *game, unsigned int x_current, unsigned int y_current, unsigned int x_next, unsigned int y_next)
{	
	PIECE *piece = game -> Board[x_current][y_current];
	
	if (game->Board[x_next][y_next])  /* eating*/
	{
		LogMove(game -> List, game -> Board[x_next][y_next], x_next, y_next); /* records the eating */
		/* DeletePiece(game, x_next, y_next); */
		DeletePiece(game -> Board[x_next][y_next]);
	}
	LogMove(game -> List, piece, x_current, y_current);
	game -> Board[x_current][y_current] = NULL;
	game -> Board[x_next][y_next] = piece;
	piece -> x_coord = x_next;
	piece -> y_coord = y_next;
}

int Try(GAME *game, PIECE *King, unsigned int x_current, unsigned int y_current, unsigned int x_next, unsigned int y_next) {
	PIECE *piece = game -> Board[x_current][y_current];
	PIECE *temp = NULL;
	int output = 0;
	
	
	if (game->Board[x_next][y_next])  /* eating*/
		temp = game -> Board[x_next][y_next];

	game -> Board[x_current][y_current] = NULL;
	game -> Board[x_next][y_next] = piece;
	piece -> x_coord = x_next;
	piece -> y_coord = y_next;

	output = LookForCheck(game -> Board, King, King -> x_coord, King -> y_coord);

	game -> Board[x_current][y_current] = game -> Board[x_next][y_next];
	piece -> x_coord = x_current;
	piece -> y_coord = y_current;

	if(temp)
		game -> Board[x_next][y_next] = temp;
	else
		game -> Board[x_next][y_next] = NULL;


	return output;
}