// Filip Bednár
// xbedna63
// VUT FIT
// príklad (b 
// 14.4.2016

#include "htable.h"

  void htab_foreach( htab_t *t, void ( *function )( const char *, unsigned int ) )
	{
		if ( t == NULL )
		{
			fprintf( stderr, "%s\n", "ERROR: table" );
			return;
		}
	
		struct htab_listitem *h_item = NULL ;
		for ( unsigned int i = 0; i < t->htab_size; i++ )
			{
	
			h_item = t->ptr[i];
				while ( h_item != NULL )
					{
						function( h_item->key, h_item->data );
						h_item = h_item->next;
					}
			}
		}
