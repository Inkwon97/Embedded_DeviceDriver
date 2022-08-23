#include <xinu.h>

extern char framebuffer[16][16];  /* shared buffer */
extern int cursor_col,cursor_row;
extern int fb_x,fb_y;

#define 	N	16

devcall	fbputc (
                struct dentry *devptr,
                char ch
                )
{

        framebuffer[fb_x][fb_y] = ch;          
	fb_y++;
        if (fb_y>= N){
            fb_y = 0;
            fb_x++;
            if(fb_x>=N){
                return SYSERR;
            }
        }

	return OK;
}
