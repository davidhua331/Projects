#ifndef MOVELIST_H
#define MOVELIST_H

#include <stdlib.h>
#include <assert.h>
#include "Game.h"
#include "Structures.h"

MOVE *CreateMove(PIECE *item, unsigned int x, unsigned int y, color shade, unit_type unit);
LMOVES *CreateList();


void DeleteMove(LMOVES *list);
void DeleteList(LMOVES *list);

/* void DeleteMove(MOVE *move);
void DeleteList(LMOVES *moveList); */


void AppendMove(LMOVES *list, MOVE *move);
void LogMove(LMOVES *list, PIECE *piece, unsigned int x, unsigned int y);
void Undo(PIECE *board[8][8], LMOVES *list);


#endif
