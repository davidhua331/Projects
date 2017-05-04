#ifndef _BOARD_H
#define _BOARD_H
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "string.h"
#include "Board.h"
#include "Game.h"

#define MAX_MSGLEN  100 
#define SQUARE_SIZE 50  
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  (8*SQUARE_SIZE)
#define BOARD_HEIGHT (8*SQUARE_SIZE)
#define WINDOW_WIDTH  (BOARD_WIDTH + 2*BOARD_BORDER)
#define WINDOW_HEIGHT (BOARD_HEIGHT + 2*BOARD_BORDER)

GtkWidget *window ;  
GtkWidget *fixed ; 
GtkWidget *chess_icon ; 
GtkWidget *table ; 

void Display(int argc, char *argv[], GAME *game);

void ResetBoard();

gint area_click(GtkWidget *widget, GdkEvent  *event, gpointer  data);

void DrawBoard(GAME *game);

void DrawBackground();


enum GRID
{
	BLACK = 0,
	WHITE = 1,
	WKING,
	WQUEEN,
	WBISHOP,
	WKNIGHT,
	WROOK,
	WPAWN,
	BKING,
	BQUEEN,
	BBISHOP,
	BKNIGHT,
	BROOK,
	BPAWN
};

static gboolean on_delete_event(GtkWidget *widget, GdkEvent  *event, gpointer   data)
{
  /* If you return FALSE in the "delete_event" signal handler,
   * GTK will emit the "destroy" signal. Returning TRUE means
   * you don't want the window to be destroyed.
   *
   * This is useful for popping up 'are you sure you want to quit?'
   * type dialogs.
   */

  g_print ("delete event occurred\n"); 
  gtk_main_quit();
  return TRUE;
}

#endif