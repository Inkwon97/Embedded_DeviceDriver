#include <xinu.h>
#include <string.h>
extern int fb_x,fb_y;
extern int cursor_row,cursor_col; //current cursor location

devcall	fbctl (
	struct dentry	*devptr,
	char* command, //ctl command
	int32 move_x, //x move count
	int32 move_y //y move count
	)
{
	cursor_row = 0; cursor_col=0;
	int i = 0; int j = 0;
	if(!strncmp(command,"forward", 8)){
  		cursor_col += 1;
		putchar('\x1B'); putchar('['); putchar('1'); putchar('C');
	} else if(!strncmp(command,"backward", 9)){
		cursor_col -= 1;
		putchar('\x1B'); putchar('['); putchar('1'); putchar('D');
	} else if(!strncmp(command,"up", 3)){
		cursor_row -= 1;
		putchar('\x1B'); putchar('['); putchar('1'); putchar('A');
	} else if(!strncmp(command,"down", 5)){
		cursor_row += 1;
		putchar('\x1B'); putchar('['); putchar('1'); putchar('B');
	} else if(!strncmp(command,"next_line", 10)){
		cursor_col = 0;
		cursor_row += 1;
		for(i=0 ; i<cursor_row ; i++){
		putchar('\x1B'); putchar('['); putchar('1'); putchar('D'); // line_down
		putchar('\x1B'); putchar('['); putchar('1'); putchar('B');
		}
	} else if(!strncmp(command,"move", 5)){
		cursor_col = 0; cursor_row = 0;
		putchar('\033'); putchar('['); putchar(';'); putchar('H');
		for(i=0 ; i < move_x ; i++){
			cursor_col++;
			if(cursor_col >= 16){
				cursor_col = 15;
				break;
			}
			else {
				putchar('\x1B'); putchar('['); putchar('1'); putchar('C');
			}
		}

		for(j=0 ; j < move_y ; j++){
			cursor_row++;
			if(cursor_row >= 16){
				cursor_row = 15;
				break;
			}
			else {
				putchar('\x1B'); putchar('['); putchar('1'); putchar('B');
			}
		}
	return OK;
	} else if(!strncmp(command,"reset", 6)){
		cursor_col = 0; cursor_row = 0;
		putchar('\033'); putchar('['); putchar(';'); putchar('H');
	}
		
}
















