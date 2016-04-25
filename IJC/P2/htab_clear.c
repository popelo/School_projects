// Filip Bednár
// xbedna63
// VUT FIT
// príklad (b 
// 14.4.2016

#include "htable.h"

  void htab_clear( htab_t *t )
	{
		if ( t->ptr == NULL || t == NULL )
			return;

		for ( unsigned int j = 0; j < t->htab_size; j++ )
			{
				if ( t->ptr[j] == NULL )
					continue;
				
				struct htab_listitem *h_item = t->ptr[j];
				while ( h_item != NULL )
					{
						struct htab_listitem *h_item_next = h_item->next;
						if ( h_item->key != NULL )
							free( h_item->key );
						
						if ( h_item != NULL )
							free( h_item );
		
						h_item = h_item_next;
					}
			
				t->ptr[j] = NULL;
			}
	}
