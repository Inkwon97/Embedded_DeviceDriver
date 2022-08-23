#include <xinu.h>
extern char framebuffer[16][16];  /* shared buffer */

int cursor_row,cursor_col;
int fb_x,fb_y;


devcall	fbflush (
	  struct dentry *devptr	/* Entry in device switch table */
	  /*char	(*fb)[16]*/			/* Buffer to hold bytes		*/
			/* Max bytes to read		*/
	)
{
	int i, j;
	sleep(2);
	for(i = 0; i < 16; i++)
	{
		if (i == 0){
			putchar('\033'); putchar('['); putchar('2'); putchar('J'); //erase screen
			putchar('\033'); putchar('['); putchar(';'); putchar('H'); //cursor homing
		}
		for(j = 0; j < 16; j++)
		{
			fbctl(CONSOLE, "reset",0,0); //cursor reset
			fbctl(CONSOLE,"move",j,i); //cursor move
			putc(CONSOLE, framebuffer[cursor_row][cursor_col]); // putc in current cursor
			sleep(0.3);
		}

	}
	putc(CONSOLE, '\n');
	return OK;
}
