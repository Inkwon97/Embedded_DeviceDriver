#include <xinu.h>
extern char framebuffer[16][16];  /* shared buffer */
extern int cursor_col,cursor_row;
extern int fb_x,fb_y;

devcall fbwrite(
                struct dentry *devptr,
                char *buff[16]
                )
{
   	int i,j;

	for(i=0;i<16;i++)
	{
		char ch[16]={};
		for(j = 0;j < 16; j++)
		{
			ch[j] = buff[i][j];
		}
		for(j = 0;j < 16; j++)
		{
			fbputc(devptr,ch[j]);
		}
		
	}	
   	return OK;
}
