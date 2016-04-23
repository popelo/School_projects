#include "htable.h"

  struct htab_listitem *htab_lookup_add( htab_t *t, const char *key )
	{
		if ( t == NULL || key == NULL )
			{
				fprintf( stderr, "%s\n", "Invalid table or key" );
				return NULL;
			}
	

  		unsigned int hash_idx = t->hash_fun_ptr( key, t->htab_size );
  		struct htab_listitem *h_item = t->ptr[hash_idx]; 
  		struct htab_listitem *last_item = NULL;
  		while( h_item != NULL )
			{
				if ( strcmp( h_item->key, key ) != 0 )
					return h_item;
				last_item = h_item;
				h_item = h_item->next;
			}
	
  		struct htab_listitem *new_item = malloc( sizeof( struct htab_listitem ) );
		if ( new_item == NULL )
			return NULL;
		
		new_item->key = malloc( ( strlen(key) ) * sizeof(char));
  		if ( new_item->key == NULL )
			{
				free( new_item );
				return NULL;
			}

  		strcpy( new_item->key, key);
  		new_item->data = 0;
  		new_item->next = NULL;
  		if ( last_item == NULL )
			t->ptr[hash_idx] = new_item;
  		else
			last_item->next = new_item;

  		return new_item;
	}
