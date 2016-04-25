// Filip Bednár
// xbedna63
// VUT FIT
// príklad (b 
// 14.4.2016

#include "io.h"

   int get_word( char *s, int max, FILE *f )
	{
		int i = 1;
		int ch;		
		int flag = 0;
		if ( f == NULL )
			return EOF;
	
		while ( ( ( ch = fgetc( f ) ) != EOF) && isspace( ch ) );
		
		if ( ch == EOF )
			return EOF;
		*s = ch;
		while( !isspace( ch = fgetc( f ) ) )
			{
				if ( ch == EOF )
					{
						s[i] = '\0';
						return EOF;
					}
				
				s[ i ] = ch;
				i++;
					if ( i  > max -2 )
						{
							s[ i ] = '\0';
							while ( !isspace ( fgetc( f ) ) ) 
								i++;
							if ( flag == 0 )
								{
									fprintf(stderr, "%s\n", "Error: Word limit reached");
									flag=1;	
								}						
							return i;		
						}
			}
		s[i] = '\0';
		return i;
	}
