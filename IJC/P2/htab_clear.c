#include "htable.h"

  void htab_clear( htab_t *t )
	{
		if ( t->ptr == NULL || t == NULL)
			return;

		for ( unsigned int i = 0; i < t->htab_size; i++ )
			{
				if ( t->ptr[i] == NULL )
					continue;
				
				struct htab_listitem *h_item = t->ptr[i];
				while ( h_item != NULL )
					{
						struct htab_listitem *h_item_next = h_item->next;
						if ( h_item->key != NULL )
							free( h_item->key );
						
						if ( h_item != NULL )
							free( h_item );
		
						h_item = h_item_next;
					}
				t->ptr[i] = NULL;
			}
	}
