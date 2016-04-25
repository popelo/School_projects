// Filip Bednár
// xbedna63
// VUT FIT
// príklad (b 
// 14.4.2016

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "htable.h"
#include "io.h"

#define MAX_LENGTH 127
 
  const unsigned int tb_size = 49157;
  
  void tb_print( const char *key, unsigned int value )
	{
		printf( "%s\t%u\n", key, value );
	}

  int main(void)
	{
		htab_t *tb = htab_init( tb_size );
		if ( tb == NULL )
			{
				fprintf( stderr, "%s\n", "ERROR : allocation" );
				return 1;
			}
		
		char word[ 1 + MAX_LENGTH ];
		while ( get_word( word, MAX_LENGTH, stdin ) != EOF )
			{
				struct htab_listitem *h_item = NULL;
				if ( ( h_item = htab_lookup_add( tb, word ) ) == NULL )
					{
						fprintf( stderr, "%s\n", "ERROR : allocation" );
						htab_free( tb );
						return 1;	
					}
				
				h_item->data++;
			}
		htab_foreach( tb, tb_print );
		htab_free( tb );
		return 0;
	}

