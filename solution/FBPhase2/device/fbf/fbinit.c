#include <xinu.h>

#include <stdio.h>
#include <string.h>

#define N 16

char framebuffer[16][16];  /* shared buffer */
int cursor_row,cursor_col;
int fb_x,fb_y;

devcall fbinit (
	  struct dentry *devptr		/* Entry in device switch table */
	)
{
  	cursor_row = cursor_col = 0;
  	fb_x = fb_y = 0;

	return OK;
}
