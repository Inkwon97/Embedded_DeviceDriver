#include <xinu.h>

devcall	fbopen (
	  struct dentry *devptr		/* Entry in device switch table */
	)
{
	putchar('\033');putchar('[');putchar('2');putchar('J'); // erase screen
	putchar('\033');putchar('[');putchar(';');putchar('H'); //cursor home
	return OK;
}
