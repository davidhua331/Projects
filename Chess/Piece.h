#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Structures.h"
#include "MoveList.h"

PIECE *CreatePiece(color shade, unit_type unit, unsigned int x, unsigned int y);

void DeletePiece(PIECE *piece);

/* void DeletePiece(GAME *game, unsigned int x, unsigned int y); */

void move(GAME *game, unsigned int x_current, unsigned int y_current, unsigned int x_next, unsigned int y_next);

int Try(GAME *game, PIECE *King, unsigned int x_current, unsigned int y_current, unsigned int x_next, unsigned int y_next);

#endif
