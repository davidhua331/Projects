#ifndef GAME_H
#define GAME_H

#include "MoveList.h"
#include "Piece.h"
#include "Structures.h"
#include "PossibleMoves.h"

GAME *CreateGame();
void DeleteGame(GAME *game);
void SetBoard(PIECE *Board[8][8]);

#endif
