#include "htable.h"

  void htab_clear( htab_t *s )
	{
		if ( s->ptr == NULL || s == NULL)
			return;

		for ( unsigned int i = 0; i < s->htab_size; i++ )
			{
				if ( s->ptr[i] == NULL )
					continue;
				
				struct htab_listitem *h_item = s->ptr[i];
				while ( h_item->key != NULL )
					{
						struct htab_listitem *h_item_next = h_item->next;
						if ( h_item->key != NULL )
							free( h_item->key );
						
						if ( h_item != NULL )
							free( h_item );
		
						h_item = h_item_next;
					}
				s->ptr[i] = NULL;
			}
	}
