#include "MoveList.h"

MOVE *CreateMove(PIECE *item, unsigned int x_coord, unsigned int y_coord, color shade, unit_type unit) 
{
	MOVE *move;
	move = malloc(sizeof(MOVE));
	move -> List = NULL;
	move -> Next = NULL;
	move -> Prev = NULL;
	move -> piece = item;
	move -> x = x_coord;
	move -> y = y_coord;
	move -> value = shade;
	move -> type = unit;
	return move;
}

LMOVES *CreateList() {
	LMOVES *moveList;
	moveList = malloc(sizeof(LMOVES));
	moveList -> numMoves = 0;
	moveList -> First = NULL;
	moveList -> Last = NULL;

	return moveList;
}

void DeleteMove(LMOVES *list) {
	MOVE *move;
	assert(list);
	if(list->numMoves){
		move = list -> Last;
		if(list -> numMoves == 1){
			list -> First = NULL;
			list -> Last = NULL;
		}
		else{
			list -> Last = move -> Prev;
			list -> Last -> Next = NULL;
		}
		free(move);
		list->numMoves--;
	}
}

/* void DeleteMove(MOVE *move) {
	LMOVES *list;
	assert(move);
	list = move -> List;
	if(list -> numMoves == 1) {
		list -> First = NULL;
		list -> Last = NULL;
	}
	else {
		list -> Last = move -> Prev;
		list -> Last -> Next = NULL;
	}
	free(move);
	list -> numMoves--;
}

void DeleteList(LMOVES *moveList) {
	MOVE *e, *n;

	assert(moveList);
	e = moveList -> Last;
	while(moveList -> numMoves)
	{
		n = e -> Prev;
		DeleteMove(e);
		e = n;
		moveList -> numMoves--;
	}
	free(moveList);
} */

void DeleteList(LMOVES *list) {
	assert(list);
	while(list->numMoves) {
		DeleteMove(list);
	}
	free(list);
}

void AppendMove(LMOVES *list, MOVE *move) {
	assert(move);
	assert(list);
	move -> List = list;
	if(!list -> numMoves){
		list -> First = move;
		move -> Prev = NULL;
	}
	else {
		move -> Prev = list -> Last;
		list -> Last -> Next = move;
	}
	list -> Last = move;
	move -> Next = NULL;

	list -> numMoves++;
}

void LogMove(LMOVES *list, PIECE *piece, unsigned int x, unsigned int y){
	MOVE *move;
	move = CreateMove(piece, x, y, piece -> value, piece -> type);
	AppendMove(list, move);
}

void Undo(PIECE *board[8][8], LMOVES *list) {
	MOVE *lastMove;
	PIECE *piece;
	unsigned int x, y;

	if(list -> numMoves) {
		lastMove = list -> Last;
		x = lastMove -> piece -> x_coord;
		y = lastMove -> piece -> y_coord;
		board[lastMove -> x][lastMove -> y] = lastMove -> piece;
		lastMove -> piece -> x_coord = lastMove -> x;
		lastMove -> piece -> y_coord = lastMove -> y;

		if(lastMove -> Prev && !lastMove -> Prev -> piece) {
			piece = CreatePiece(lastMove -> Prev -> value, lastMove -> Prev -> type, x, y);
			board[x][y] = piece;
		}
		else
			board[x][y] = NULL;
		DeleteMove(list);
	}
}