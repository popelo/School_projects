#include "htable.h"

  void htab_clear( htab_t *s )
	{
		if ( s->ptr == NULL || s == NULL)
			return;

		for ( unsigned int i = 0; i < s->htab_size; i++ )
			{
				if ( s->ptr[i] == NULL )
					continue;
				
				struct htab_listitem *f_item = s->ptr[i];
				while ( f_item->key != NULL )
					{
						struct htab_listitem *f_item_next = f_item->next;
						if ( f_item->key != NULL )
							free( f_item->key );
						
						if ( f_item != NULL )
							free( f_item );
		
						f_item = f_item_next;
					}
				s->ptr[i] = NULL;
			}
	}
