// Filip Bednár
// xbedna63
// VUT FIT
// príklad (a 
// 14.4.2016

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define buff_size 510 //maximum length of a line
#define PRINT_LINES 10 //default value , how many lines will be printed

	//function to find out, if string from argument is number, returns non-zero value if it is number
  int isnum( char *str )
	{
		int i = 0;
		while ( str[i] != '\0')	// length of string
				i++;

		for ( int k = 0; k<i; k++ ) // verification
			{
				if ( str[k] < 48 || str[k] > 57 )
					return 1;
			}
	
		return 0;
	} 

	//function for printing last X lines from file, default 10
  void tail( FILE *file , unsigned long print_lines ) 
	{
		
		if ( print_lines == 0 ) // no lines to print
			return ;

		if ( file == NULL ) // if there isn't any file, reads from console(stdin)
			file = stdin ;

		char buffer[ print_lines ][ buff_size ] ; // variable length array
		int ch; // for testing characters
		int flag = 0; //for cropping
		unsigned long i = 0 ; // not in for, need later this value
		
		for( ; ; ++i) //reading
			{
				if ( fgets( buffer[ i % print_lines ], buff_size, file) == NULL ) 
					break;
				
				if (strchr(buffer[ i % print_lines], '\n') == NULL) //case we need to crop line
					{
						if( flag == 0 )
							fprintf( stderr, "Line is too long... cropping \n" );

						flag = 1 ;
						buffer[ i % print_lines ][ buff_size - 2 ] = '\n' ;
						while( ( ch = getc( file ) ) != '\n' && ch != EOF); //cropping the rest
					}
			}

		if ( print_lines > i ) // in case that, less lines than we want to print
			print_lines = i;
		
		for (unsigned long k = 0 ; k < print_lines ; ++k, ++i ) // printing
			printf("%s", buffer[i % print_lines]);
	
	}
  
  int main( int argc, char *argv[] )
	{
		FILE *file;		
		unsigned long print_lines = PRINT_LINES; //default number of lines to print
		char *ptr; // pointer for strtoul
		
		if ( argc > 4  ) // max number of arguments
			{
				fprintf( stderr, "Too many arguments\n" );
				return 1;
			}

		if ( argc == 1 ) // no arguments for function ---> reading from console(stdin)
			{
				file = NULL ; //reading from stdin	
			}
		
		if ( argc == 2 ) // if - then reading from stdin , if file then reading from it
			{
				if(strcmp( argv[1], "-") == 0 )
					file = NULL ;
				else
					{
						file = fopen( argv[1], "r" );
						if ( file == NULL ) // empty file
							{
								fprintf( stderr, "Empty file or invalid argument\n" );
								return 1;
							}
					}
			}
		
		if ( argc == 3 ) // if arguments -n x(number) 
			{
				if (strcmp(argv[1] , "-n") == 0)
                                        {
                                                if( isnum( argv[2] ) == 0 )
							print_lines = strtoul( argv[2] , &ptr , 0); // char to long
						else
							{
								 fprintf( stderr, "Invalid arguments\n" );
								return 1;
							}
						file = NULL ; // reading from stdin
					}
                                else
                                        {
                                                fprintf( stderr, "Invalid arguments\n" );
                                                return 1;
                                        }
			}
	
		if ( argc == 4 ) // if arguments -n x(number) and file
			{
				if (strcmp( argv[1] , "-n" ) == 0 )
					{
						if ( isnum( argv[2] ) == 0 )
							print_lines = strtoul( argv[2] , &ptr , 0);
                                                else
							{
 								fprintf( stderr, "Invalid arguments\n" );
								return 1;
							}
						file = fopen( argv[1], "r" );
                                                
						if (file == NULL)
                                                        {
                                                                fprintf( stderr, "Empty file\n" );
                                                                return 1;
                                                        }
                                        }
				else
					{
						fprintf( stderr, "Invalid arguments\n" );
						return 1;
					}
						
			}
				
		tail(file, print_lines); // calling function
		return 0;	
	
	}


