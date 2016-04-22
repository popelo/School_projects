#include "htable.h"

  void htab_foreach( htab_t *t, void ( *function )( const char *, unsigned int ) )
	{
		if ( t == NULL )
		{
			fprintf( stderr, "%s\n", "Invalid table(foreach)" );
			return;
		}
	
		struct htab_listitem *h_item = NULL ;
		for ( unsigned int j = 0; j < t->htab_size; j++)
			{
				h_item = t->ptr[j];
				while ( h_item != NULL )
					{
						function(h_item->key, h_item->data);
						h_item = h_item->next;
					}
	}
}
