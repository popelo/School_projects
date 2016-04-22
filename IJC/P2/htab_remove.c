#include "htable.h"

  void htab_remove( htab_t *t, const char *key )
	{
		if ( t == NULL || key == NULL )
			{
				fprintf( stderr, "%s\n", "Invalid table or key" );
				return;
			}
		
		unsigned int hash_idx = t->hash_fun_ptr( key, t->htab_size );
		struct htab_listitem *h_item = t->ptr[hash_idx];
		struct htab_listitem *last_item = NULL;
		while ( h_item != NULL )
			{
				if ( !strcmp( h_item->key, key ) )
					{
						if ( h_item->next == NULL && last_item = NULL )
							t->ptr[hash_idx] = NULL;
					}
				
				else if ( h_item->next == NULL && last_item != NULL ) 
						last_item->next = NULL;
			
				else if (last_item != NULL && h_item->next != NULL) 
						last_item->next = h_item->next;
	
				else 
						t->ptr[hash_idx] =  h_item->next;
			
				free(h_item->key);
				h_item->next = NULL;
				free(h_item);
				break;
			}

		last_item = h_item;
		h_item = h_item->next;
	}
	
