/* xsh_ps.c - xsh_ps */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/* app on ring buffer source code */

/*----------------------------------------------------------------------------
 *    prod2   --
 *----------------------------------------------------------------------------
 */
void prod2()
{

    int i,j;
    char c;

    char *fb[16] = {

	    {"    *******     "},
	    {"       *        "},
	    {"     *****      "},
	    {"    ** * **     "},
	    {"    *  *  *     "},
	    {"    *  *  *     "},
	    {"    *  *  *     "},
	    {"    *  *  *     "},
	    {"     *****      "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "}	    
	    
	   
    };

        init(FBUF15);
	fbopen(FBUF15);
	/*for(i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			putc(FBUF15, fb[i][j]);
		}
	}*/
	fbwrite(FBUF15,fb);
	fbflush(FBUF15);

}

void prod3()
{

    int i,j;
    char c;

    char *fb[16] = {

	    {"       *        "},
	    {"     *   *      "},
	    {"   *       *    "},
	    {" *           *  "},
	    {"*             * "},
	    {"*             * "},
	    {"*             * "},
	    {"  ***********   "},
	    {"    *  *  *     "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "},
	    {"       *        "}	    
	    
	   
    };

        init(FBUF15);
	fbopen(FBUF15);
	/*for(i = 0; i < 16; i++)
	{
		for (j = 0; j < 16; j++)
		{
			putc(FBUF15, fb[i][j]);
		}
	}*/
	fbwrite(FBUF15,fb);
	fbflush(FBUF15);

}
/*--------------------------------------------------------------------------
 *    ring --  producer and consumer process synchronized with semaphores
 *--------------------------------------------------------------------------
*/
void ring(int num)
{
	switch(num)
	{
	case 1:  
		resume( create(prod2, 1000, 20, "prod", 0, NULL));
		break;
	case 2:
		resume( create(prod3, 1000, 20, "prod", 0, NULL));
		break;
	}

}


/*------------------------------------------------------------------------
 * xsh_ps - shell command to print the process table
 *------------------------------------------------------------------------
 */
shellcmd xsh_ps(int nargs, char *args[])
{
	struct	procent	*prptr;		/* pointer to process		*/
	int32	i;			/* index into proctabl		*/
	char *pstate[]	= {		/* names for process states	*/
		"free ", "curr ", "ready", "recv ", "sleep", "susp ",
		"wait ", "rtime"};

	/* For argument '--help', emit help about the 'ps' command	*/

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Use: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tDisplays information about running processes\n");
		printf("Options:\n");
		printf("\t--help\t display this help and exit\n");
		return 0;
	} else if (nargs == 2 && strncmp(args[1], "ES2", 4) == 0) {
		ring(1);
		return 0;
	} else if (nargs == 2 && strncmp(args[1], "ES3", 4) == 0) {
		ring(2);
		return 0;
	}

	/* Check for valid number of arguments */

	if (nargs > 1) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
				args[0]);
		return 1;
	}

	/* Print header for items from the process table */

	printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
		   "Pid", "Name", "State", "Prio", "Ppid", "Stack Base",
		   "Stack Ptr", "Stack Size");

	printf("%3s %-16s %5s %4s %4s %10s %-10s %10s\n",
		   "---", "----------------", "-----", "----", "----",
		   "----------", "----------", "----------");

	/* Output information for each process */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		if (prptr->prstate == PR_FREE) {  /* skip unused slots	*/
			continue;
		}
		printf("%3d %-16s %s %4d %4d 0x%08X 0x%08X %8d\n",
			i, prptr->prname, pstate[(int)prptr->prstate],
			prptr->prprio, prptr->prparent, prptr->prstkbase,
			prptr->prstkptr, prptr->prstklen);
	}
	return 0;
}
