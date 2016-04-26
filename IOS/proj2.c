#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  int main( int argc, char *argv[] )
	{
		//TRASH
			(void)argc;
		//TRASH
		
		long int P;
		long int C;
		int PT;
		int RT;
		char *ptr; //pre strtol
		
		//potom podmienky

		//predávanie argumentov
		P = strtol( argv[1], &ptr, 10);
		C = strtol( argv[2], &ptr, 10);
		PT = atoi(argv[3]);
		RT = atoi(argv[4]);
		
	
			
	
		return 0;
	}
