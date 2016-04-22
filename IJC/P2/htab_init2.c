#include "htable.h"

  htab_t *htab_init2( unsigned int size, unsigned int ( *hashfunction)( const char *str, unsigned htab_size ) )
	{
		htab_t *new_tb = malloc(sizeof(htab_t) + size * sizeof(struct htab_listitem *));
		if (new_tb == NULL)
			return NULL;
	
		for (unsigned int i = 0; i < size; i++)
			{
				new_tb->ptr[i] = NULL;
			}

		new_tb->htab_size = size;
		new_tb->n = 0;
		new_tb->hash_fun_ptr = hashfunction;
		return new_tb;
	}
