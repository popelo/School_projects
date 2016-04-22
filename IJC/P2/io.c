#include "io.h"

   int get_word( char *s, int max, FILE *f )
	{
		if ( f == NULL )
			return EOF;
	
		int i = 1;
		int ch;
	
		while ( ( ch = fgetc( f ) != EOF) && isspace( ch ) );
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
				
				s[i] = ch;
				i++;
				if (i > max-1)
					{
						while ( !isspace( fgetc( f ) ) );
						fprintf( stderr, "%s\n", "Maximum word length was reached" );
						break;
					}
			}
		s[i] = '\0';
		return i;
	}
