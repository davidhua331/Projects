#include "Game.h"

GAME *CreateGame() {
	GAME *game;
	game = malloc(sizeof(GAME));
	game -> List = CreateList();
	game -> PossibleMoves = CreateListOfPossibleMoves();
	SetBoard(game -> Board);

	game -> WhiteKing = game -> Board[4][0];
	game -> BlackKing = game -> Board[4][7];

	return game;
}

void DeleteGame(GAME *game) {
	assert(game);
	int i, j;
	DeleteList(game -> List);
	for(j = 0; j < 8; j++) {
		for(i = 0; i < 8; i++) {
			if(game -> Board[i][j]) {
				DeletePiece(game -> Board[i][j]);
			}
		}
	}
	DeleteListOfPossibleMoves(game -> PossibleMoves);

	free(game);
}



void SetBoard(PIECE *Board[8][8])
{
	
	PIECE *piece;
	int i, j;
	for(j=2; j<6; j++)
	{
		for(i=0; i<8; i++)
		{
			Board[i][j] = NULL;
		}
	}
	piece = CreatePiece(white, rook, 0, 0);
	Board[0][0] = piece;
	piece = CreatePiece(white, knight, 1, 0);
	Board[1][0] = piece;
	piece = CreatePiece(white, bishop, 2, 0);
	Board[2][0] = piece;
	piece = CreatePiece(white, queen, 3, 0);
	Board[3][0] = piece;
	piece = CreatePiece(white, king, 4, 0);
	Board[4][0] = piece;
	piece = CreatePiece(white, bishop, 5, 0);
	Board[5][0] = piece;
	piece = CreatePiece(white, knight, 6, 0);
	Board[6][0] = piece;
	piece = CreatePiece(white, rook, 7, 0);
	Board[7][0] = piece;
	for( i=0; i<8; i++)
	{
		j = 1;
		piece = CreatePiece(white, pawn, i, j);
		Board[i][j] = piece;
	}
	piece = CreatePiece(black, rook, 0, 7);
	Board[0][7] = piece;
	piece = CreatePiece(black, knight, 1, 7);
	Board[1][7] = piece;
	piece = CreatePiece(black, bishop, 2, 7);
	Board[2][7] = piece;
	piece = CreatePiece(black, queen, 3, 7);
	Board[3][7] = piece;
	piece = CreatePiece(black, king, 4, 7);
	Board[4][7] = piece;
	piece = CreatePiece(black, bishop, 5, 7);
	Board[5][7] = piece;
	piece = CreatePiece(black, knight, 6, 7);
	Board[6][7] = piece;
	piece = CreatePiece(black, rook, 7, 7);
	Board[7][7] = piece;
	for( i=0; i<8; i++)
	{
		j = 6;
		piece = CreatePiece(black, pawn, i, j);
		Board[i][j] = piece;
	}
}
