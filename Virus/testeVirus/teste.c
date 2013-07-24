#include <stdio.h>
#include <kmod.h>

int main()
{
	call_usermodehelper("virus.c", 0, 0, 0);
	
	
	printf("\nOk!\n\n");
	return 0;
}

