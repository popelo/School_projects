#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//ošetriť pretečenie

   int isnum( char *str )
	{
		int i = 0;
		while ( str[i] != '\0')	
				i++;

		for ( int k = 0; k<i; k++ ) 
			{
				if ( str[k] < 48 || str[k] > 57 )
					return 1;
			}
		return 0;
	}
  

	
  
  int main( int argc, char *argv[] )
	{		
		//premenné vstup,práca sním
		unsigned long P,C,PT,RT;
		char *ptr; //pre strtol
		 
		 

		//ošetrenie vstupu 
		if ( argc != 5 )
			{
				fprintf( stderr, "ERROR: Invalid input\n");
				exit(1);
			}
		for (unsigned int i = 1 ; i <= 4 ; i++ )
			{	
				if ( ( isnum( argv[i] ) ) == 1 )
					{
						fprintf( stderr, "ERROR: Invalid input\n");
						exit(1);
					}
			}

		//predávanie argumentov
		P = strtoul( argv[1], &ptr, 10);
		C = strtoul( argv[2], &ptr, 10);
		PT = strtoul( argv[3], &ptr, 10);
		RT = strtoul( argv[4], &ptr, 10);
		
		//TRASH
		(void)P;
		(void)C;
		(void)PT;
		(void)RT;	
			
	
		return 0;
	}
