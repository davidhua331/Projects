#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include "string.h"
#include "Board.h"
#include "Game.h"
/*Global Variables */

enum GRID Background[8][8];

void ResetBoard()
{
	Background[0][0] = BLACK;
	Background[1][0] = WHITE;
	Background[2][0] = BLACK;
	Background[3][0] = WHITE;
	Background[4][0] = BLACK;
	Background[5][0] = WHITE;
	Background[6][0] = BLACK;
	Background[7][0] = WHITE;
	Background[0][1] = WHITE;
	Background[1][1] = BLACK;
	Background[2][1] = WHITE;
	Background[3][1] = BLACK;
	Background[4][1] = WHITE;
	Background[5][1] = BLACK;
	Background[6][1] = WHITE;
	Background[7][1] = BLACK;
	Background[0][2] = BLACK;
	Background[1][2] = WHITE;
	Background[2][2] = BLACK;
	Background[3][2] = WHITE;
	Background[4][2] = BLACK;
	Background[5][2] = WHITE;
	Background[6][2] = BLACK;
	Background[7][2] = WHITE;
	Background[0][3] = WHITE;
	Background[1][3] = BLACK;
	Background[2][3] = WHITE;
	Background[3][3] = BLACK;
	Background[4][3] = WHITE;
	Background[5][3] = BLACK;
	Background[6][3] = WHITE;
	Background[7][3] = BLACK;
	Background[0][4] = BLACK;
	Background[1][4] = WHITE;
	Background[2][4] = BLACK;
	Background[3][4] = WHITE;
	Background[4][4] = BLACK;
	Background[5][4] = WHITE;
	Background[6][4] = BLACK;
	Background[7][4] = WHITE;
	Background[0][5] = WHITE;
	Background[1][5] = BLACK;
	Background[2][5] = WHITE;
	Background[3][5] = BLACK;
	Background[4][5] = WHITE;
	Background[5][5] = BLACK;
	Background[6][5] = WHITE;
	Background[7][5] = BLACK;
	Background[0][6] = BLACK;
	Background[1][6] = WHITE;
	Background[2][6] = BLACK;
	Background[3][6] = WHITE;
	Background[4][6] = BLACK;
	Background[5][6] = WHITE;
	Background[6][6] = BLACK;
	Background[7][6] = WHITE;
	Background[0][7] = WHITE;
	Background[1][7] = BLACK;
	Background[2][7] = WHITE;
	Background[3][7] = BLACK;
	Background[4][7] = WHITE;
	Background[5][7] = BLACK;
	Background[6][7] = WHITE;
	Background[7][7] = BLACK;
}


/* ----commented out
void InitBoard(GAME *game)
{
	Board[0][0] = BROOK;
	Board[1][0] = BKNIGHT;
	Board[2][0] = BBISHOP;
	Board[3][0] = BQUEEN;
	Board[4][0] = BKING;
	Board[5][0] = BBISHOP;
	Board[6][0] = BKNIGHT;
	Board[7][0] = BROOK;
	Board[0][1] = BPAWN;
	Board[1][1] = BPAWN;
	Board[2][1] = BPAWN;
	Board[3][1] = BPAWN;
	Board[4][1] = BPAWN;
	Board[5][1] = BPAWN;
	Board[6][1] = BPAWN;
	Board[7][1] = BPAWN;
	Board[0][2] = BLACK;
	Board[1][2] = WHITE;
	Board[2][2] = BLACK;
	Board[3][2] = WHITE;
	Board[4][2] = BLACK;
	Board[5][2] = WHITE;
	Board[6][2] = BLACK;
	Board[7][2] = WHITE;
	Board[0][3] = WHITE;
	Board[1][3] = BLACK;
	Board[2][3] = WHITE;
	Board[3][3] = BLACK;
	Board[4][3] = WHITE;
	Board[5][3] = BLACK;
	Board[6][3] = WHITE;
	Board[7][3] = BLACK;
	Board[0][4] = BLACK;
	Board[1][4] = WHITE;
	Board[2][4] = BLACK;
	Board[3][4] = WHITE;
	Board[4][4] = BLACK;
	Board[5][4] = WHITE;
	Board[6][4] = BLACK;
	Board[7][4] = WHITE;
	Board[0][5] = WHITE;
	Board[1][5] = BLACK;
	Board[2][5] = WHITE;
	Board[3][5] = BLACK;
	Board[4][5] = WHITE;
	Board[5][5] = BLACK;
	Board[6][5] = WHITE;
	Board[7][5] = BLACK;
	Board[0][6] = WPAWN;
	Board[1][6] = WPAWN;
	Board[2][6] = WPAWN;
	Board[3][6] = WPAWN;
	Board[4][6] = WPAWN;
	Board[5][6] = WPAWN;
	Board[6][6] = WPAWN;
	Board[7][6] = WPAWN;
	Board[0][7] = WROOK;
	Board[1][7] = WKNIGHT;
	Board[2][7] = WBISHOP;
	Board[3][7] = WQUEEN;
	Board[4][7] = WKING;
	Board[5][7] = WBISHOP;
	Board[6][7] = WKNIGHT;
	Board[7][7] = WROOK;

}
----------------- */

/*
void ReverseGridColor(int g_x, int g_y)
{
	if(Background[g_x][g_y] == BLACK)
	{
		Background[g_x][g_y] = WHITE;
	}
	else
	{
		Background[g_x][g_y] = BLACK;
	}
}
*/

void DrawBackground()
{
	int i, j;

	for(j = 7; j >=0; j --)
	{
		for(i = 0; i < 8; i ++)
		{
			switch(Background[i][j])
			{
				case BLACK:
					chess_icon = gtk_image_new_from_file("./chess_icon/Bsquare.jpg") ;
					break;
				case WHITE:
					chess_icon = gtk_image_new_from_file("./chess_icon/Wsquare.jpg") ;
					break;
				default:
					break;
			}
			gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}
}

void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
	*g_x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	*g_y = 7 - ((c_y - BOARD_BORDER) / SQUARE_SIZE);
}

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below.
 */

gint area_click (GtkWidget *widget,
                 GdkEvent  *event, 
                 gpointer  data)
{
  int x1, y1 ; 
  char words[MAX_MSGLEN] ; 
  int coord_x, coord_y, grid_x, grid_y; 

  struct BOARD *chess_board ; 
  struct SQUARE *chess_piece ;
  struct SQUARE *piece_dest ;   

  GdkModifierType state ; 

  gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ; 

  CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);

  printf("coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x, coord_y, grid_x, grid_y);

    gtk_container_remove(GTK_CONTAINER(window), fixed) ; 
    table = gtk_table_new (8, 8, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;


    /*set fixed*/

    fixed = gtk_fixed_new() ;
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(window), fixed) ;
    gtk_widget_show_all(window) ; 

  return TRUE ; 
}

void DrawBoard(GAME *game)
{
	int i, j;
	int p;
	for(j = 7; j >= 0; j--)
	{
		p=7-j;
		for(i = 0; i < 8; i++)
		{
			if(game->Board[i][j] == NULL)
			{
				switch(Background[i][j])
				{
				case BLACK:
					chess_icon = gtk_image_new_from_file("./chess_icon/Bsquare.jpg") ;
					break;
				case WHITE:
					chess_icon = gtk_image_new_from_file("./chess_icon/Wsquare.jpg") ;
					break;
				default:
					break;
				}
			}
			else{
			if( game->Board[i][j]->value == white && game->Board[i][j]->type == king )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
			}
			if( game->Board[i][j]->value == white && game->Board[i][j]->type == queen )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/WQueen.jpg") ;
			}
			if( game->Board[i][j]->value == white && game->Board[i][j]->type == bishop )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/WBishop.jpg") ;
			}
			if( game->Board[i][j]->value == white && game->Board[i][j]->type == knight )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/WKnight.jpg") ;
			}
			if( game->Board[i][j]->value == white && game->Board[i][j]->type == rook )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/WRook.jpg") ;
			}
			if( game->Board[i][j]->value == white && game->Board[i][j]->type == pawn )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/WPawn.jpg") ;
			}	
			if( game->Board[i][j]->value == black && game->Board[i][j]->type == king )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/BKing.jpg") ;
			}
			if( game->Board[i][j]->value == black && game->Board[i][j]->type == queen )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/BQueen.jpg") ;
			}
			if( game->Board[i][j]->value == black && game->Board[i][j]->type == bishop )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/BBishop.jpg") ;
			}
			if( game->Board[i][j]->value == black && game->Board[i][j]->type == knight )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/BKnight.jpg") ;
			}
			if( game->Board[i][j]->value == black && game->Board[i][j]->type == rook )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/BRook.jpg") ;
			}
			if( game->Board[i][j]->value == black && game->Board[i][j]->type == pawn )
			{
					chess_icon = gtk_image_new_from_file("./chess_icon/BPawn.jpg") ;
			}
			}
			gtk_table_attach( GTK_TABLE(table), chess_icon, i, i + 1, p, p + 1, GTK_FILL, GTK_FILL, 0, 0 ) ;
		}
	}
}

void Display(int argc, char *argv[], GAME *game)
{

  gtk_init(&argc, &argv) ;
  ResetBoard();
 
  /*create a new window */
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ; 
  gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ; 
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ; 
  gtk_window_set_title(GTK_WINDOW(window), "Chess is a Trap!") ; 
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ; 


  /*register event handlers*/
  g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ; 
  gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ; 
  g_signal_connect(window, "button_press_event", G_CALLBACK(area_click), NULL) ; 

  /*create a table and draw the board*/
  table = gtk_table_new (8, 8, TRUE) ; 
  gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ; 
  fixed = gtk_fixed_new() ; 
  gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ; 
  gtk_container_add(GTK_CONTAINER(window), fixed) ;
  DrawBoard(game); 

  /*show the window*/
  gtk_widget_show_all(window) ; 
  gtk_main() ;

}
