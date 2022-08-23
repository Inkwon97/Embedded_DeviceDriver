
#include <xinu.h>

extern char framebuffer[16][16];  /* shared buffer */
extern int fb_x,fb_y;
extern int cursor_row,cursor_col;

#define 	N	16

devcall	fbgetc (
	  struct dentry *devptr		/* Entry in device switch table */
	)
{
	char n;

        n = framebuffer[fb_x][fb_y];         /* n = dequeue() */
	fb_y++;
        if (fb_y>= N){
            fb_y = 0;
            fb_x++;
            if(fb_x>=N){
                return OK;
            }
        }

	return n;
}
