#include "PossibleMoves.h"

PMOVE *CreatePossibleMove(unsigned int i, unsigned int j) {
	PMOVE *pmove;
	pmove = malloc(sizeof(PMOVE));
	pmove -> List = NULL;
	pmove -> Next = NULL;
	pmove -> Prev = NULL;
	pmove -> x = i;
	pmove -> y = j;
	return pmove;
}

LPMOVES *CreateListOfPossibleMoves() {
	LPMOVES *list;
	list = malloc(sizeof(LPMOVES));
	list -> Length = 0;
	list -> First = NULL;
	list -> Last = NULL;
	return list;
}

void DeletePossibleMove(LPMOVES *list) {
	PMOVE *pmove;
	assert(list);
	if(list->Length){
		pmove = list -> Last;
		if(list -> Length == 1){
			list -> First = NULL;
			list -> Last = NULL;
		}
		else{
			list -> Last = pmove -> Prev;
			list -> Last -> Next = NULL;
		}
		free(pmove);
		list->Length--;
	}
}

void DeleteListOfPossibleMoves(LPMOVES *list) {
	assert(list);
	while(list->Length) {
		DeletePossibleMove(list);
	}
	free(list);
}

void AppendPossibleMove(LPMOVES *list, PMOVE *pmove) {
	assert(list);
	assert(pmove);
	if(!list->Length) {
		list -> First = pmove;
		pmove -> Prev = NULL;
	}
	else {
		list -> Last -> Next = pmove;
		pmove -> Prev = list -> Last;
	}
	list -> Last = pmove;
	pmove -> Next = NULL;
	list->Length++;
}

LPMOVES *FindPossibleMoves(GAME *game, PIECE *piece) {
	LPMOVES *newList;
	PIECE *king;
	assert(game -> PossibleMoves);
	DeleteListOfPossibleMoves(game -> PossibleMoves);
	newList = CreateListOfPossibleMoves();

	switch(piece -> type) {
		case pawn:	MovesForPawn(game -> Board, piece, newList);
				break;
		case rook:	MovesForRook(game -> Board, piece, newList);
				break;
		case knight:	MovesForKnight(game -> Board, piece, newList);
				break;
		case bishop:	MovesForBishop(game -> Board, piece, newList);
				break;
		case queen:	MovesForQueen(game -> Board, piece, newList);
				break;
		default:	MovesForKing(game -> Board, piece, newList);
	}
	switch(piece -> value) {
		case white:	king = game -> WhiteKing;
				break;
		default:	king = game -> BlackKing;
	}

	/* return newList; */

	return RefineForCheck(game, king, piece, newList);
}

void MovesForKing(PIECE *board[8][8], PIECE *piece, LPMOVES *list) {
	PMOVE *move;
	int i, j, x, y;

	for(i = -1; i < 2; i++)
		for(j = -1; j < 2; j++)
			if(i == 0 && j == 0)
				continue;
			else {
				x = piece -> x_coord + i;
				y = piece -> y_coord + j;
				if(x >= 0 && x < 8 && y >= 0 && y < 8) {
					if((!board[x][y] || (board[x][y] -> value != piece -> value)) && LookForCheck(board, piece, x, y)) {
						move = CreatePossibleMove(x, y);
						AppendPossibleMove(list, move);
					}
				}
			}
}

void MovesForQueen(PIECE *board[8][8], PIECE *piece, LPMOVES *list) {
	MovesForRook(board, piece, list);
	MovesForBishop(board, piece, list);
}

void MovesForBishop(PIECE *board[8][8], PIECE *piece, LPMOVES *list) {
	PMOVE *move;
	int mult_x, mult_y;
	int x, y, i;
	mult_x = 1;

	for(i = 0; i < 4; i++) {
		int blocked = 0;
		mult_y = (i / 2 % 2) ? -1 : 1;
		x = piece -> x_coord + mult_x;
		y = piece -> y_coord + mult_y;
		while(x >= 0 && x < 8 && y >= 0 && y < 8 && !blocked) {
			if(!board[x][y]) {
				move = CreatePossibleMove(x, y);
				AppendPossibleMove(list, move);
			}
			else if(board[x][y] -> value != piece -> value) {
				blocked = 1;
				move = CreatePossibleMove(x, y);
				AppendPossibleMove(list, move);
			}
			else
				blocked = 1;
			x += mult_x;
			y += mult_y;
		}
		mult_x = (mult_x + 1) ? -1 : 1;
	}
}

void MovesForKnight(PIECE *board[8][8], PIECE *piece, LPMOVES *list) {
	PMOVE *move;
	int x, y, i, j;
	int incr_x, incr_y, mult_x, mult_y;
	incr_x = 2;
	incr_y = 1;
	mult_x = 1;

	for(i = 0; i < 2; i++) {
		for(j = 0; j < 4; j++) {
			mult_y = (j / 2 % 2) ? -1 : 1;
			x = piece -> x_coord + incr_x * mult_x;
			y = piece -> y_coord + incr_y * mult_y;
			if(x >= 0 && x < 8 && y >= 0 && y < 8)
				if(!board[x][y] || (board[x][y] -> value != piece -> value)) {
					move = CreatePossibleMove(x, y);
					AppendPossibleMove(list, move);
				}
			mult_x = (mult_x + 1) ? -1 : 1;
		}
		incr_x = (incr_x - 1) ? 1 : 2;
		incr_y = (incr_y - 1) ? 1 : 2;
	}
}

void MovesForRook(PIECE *board[8][8], PIECE *piece, LPMOVES *list) {
	PMOVE *move;
	int mult_x, mult_y;
	int x, y, i;
	mult_x = 1;
	mult_y = 0;

	for(i = 0; i < 4; i++) {
		int blocked = 0;
		mult_x *= (i / 2 % 2) ? -1 : 1;
		mult_y *= (i / 2 % 2) ? -1 : 1;
		x = piece -> x_coord + mult_x;
		y = piece -> y_coord + mult_y;
		while(x >= 0 && x < 8 && y >= 0 && y < 8 && !blocked) {
			if(!board[x][y]) {
				move = CreatePossibleMove(x, y);
				AppendPossibleMove(list, move);
			}
			else if(board[x][y] -> value != piece -> value) {
				blocked = 1;
				move = CreatePossibleMove(x, y);
				AppendPossibleMove(list, move);
			}
			else
				blocked = 1;
			x += mult_x;
			y += mult_y;
		}
		mult_x = mult_x ? 0 : 1;
		mult_y = mult_y ? 0 : 1;
	}
}

void MovesForPawn(PIECE *board[8][8], PIECE *piece, LPMOVES *list) {
	PMOVE *move;
	int direction;
	int x, y;
	direction = (piece -> value == white) ? 1 : -1;
	x = piece -> x_coord;
	y = piece -> y_coord;

	if(!board[x][y + direction]) {
		move = CreatePossibleMove(x, y + direction);
		AppendPossibleMove(list, move);
	}
	if(x > 0 && y + direction >= 0 && y + direction < 8 && board[x - 1][y + direction] && board[x - 1][y + direction] -> value != piece -> value) {
		move = CreatePossibleMove(x - 1, y + direction);
		AppendPossibleMove(list, move);
	}

	if(x < 7 && y + direction >= 0 && y + direction < 8 && board[x + 1][y + direction] && board[x + 1][y + direction] -> value != piece -> value) {
		move = CreatePossibleMove(x + 1, y + direction);
		AppendPossibleMove(list, move);
	}
}

int LookForCheck(PIECE *board[8][8], PIECE *piece, unsigned int x, unsigned int y) {
	PIECE *temp;
	LPMOVES *list;
	PMOVE *move;
	int i;
	temp = CreatePiece(piece -> value, piece -> type, x, y);

	/* Checks for enemy pawn */
	list = CreateListOfPossibleMoves();
	MovesForPawn(board, temp, list);
	move = list -> First;
	for(i = 0; i < list -> Length; i++) {
		if(board[move -> x][move -> y] && (board[move -> x][move -> y] -> type == pawn)) {
			DeletePiece(temp);
			DeleteListOfPossibleMoves(list);
			return 0;
		}
		move = move -> Next;
	}
	DeleteListOfPossibleMoves(list);

	/* Checks for enemy bishop or queen */
	list = CreateListOfPossibleMoves();
	MovesForBishop(board, temp, list);
	move = list -> First;
	for(i = 0; i < list -> Length; i++) {
		if(board[move -> x][move -> y] && ((board[move -> x][move -> y] -> type == bishop) || (board[move -> x][move -> y] -> type == queen))) {
			DeletePiece(temp);
			DeleteListOfPossibleMoves(list);
			return 0;
		}
		move = move -> Next;
	}
	DeleteListOfPossibleMoves(list);

	/* Checks for enemy rook or queen */
	list = CreateListOfPossibleMoves();
	MovesForRook(board, temp, list);
	move = list -> First;
	for(i = 0; i < list -> Length; i++) {
		if(board[move -> x][move -> y] && ((board[move -> x][move -> y] -> type == rook) || (board[move -> x][move -> y] -> type == queen))) {
			DeletePiece(temp);
			DeleteListOfPossibleMoves(list);
			return 0;
		}
		move = move -> Next;
	}
	DeleteListOfPossibleMoves(list);

	/* Checks for enemy knight */
	list = CreateListOfPossibleMoves();
	MovesForKnight(board, temp, list);
	move = list -> First;
	for(i = 0; i < list -> Length; i++) {
		if(board[move -> x][move -> y] && (board[move -> x][move -> y] -> type == knight)) {
			DeletePiece(temp);
			DeleteListOfPossibleMoves(list);
			return 0;
		}
		move = move -> Next;
	}
	DeleteListOfPossibleMoves(list);

	DeletePiece(temp);
	return 1;
}

LPMOVES *RefineForCheck(GAME *game, PIECE *King, PIECE *piece, LPMOVES *list) {
	LPMOVES *newList;
	PMOVE *pmove, *moveToAdd;
	int i;

	assert(list);

	if(!list -> Length)
		return list;
	else {
		newList = CreateListOfPossibleMoves();
		pmove = list -> First;
		for(i = 0; i < list -> Length; i++) {
			if(Try(game, King, piece -> x_coord, piece -> y_coord, pmove -> x, pmove -> y)) {
				moveToAdd = CreatePossibleMove(pmove -> x, pmove -> y);
				AppendPossibleMove(newList, moveToAdd);
			}
			pmove = pmove -> Next;


			/* if(pmove) {
				move(game, piece -> x_coord, piece -> y_coord, pmove -> x, pmove -> y);
				if(LookForCheck(game -> Board, King, King -> x_coord, King -> y_coord)) {
					moveToAdd = CreatePossibleMove(pmove -> x, pmove -> y);
					AppendPossibleMove(newList, moveToAdd);
				}
				Undo(game -> Board, game -> List);

			} */

		}
		DeleteListOfPossibleMoves(list);
		return newList;
	}
}