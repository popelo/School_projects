#include "htable.h"

htab_t *htab_init2( unsigned int size, unsigned int ( *hashfunction)( const char *str, unsigned htab_size ) )
	{
		htab_t *newTab = malloc( size * sizeof(struct htab_listitem *) + sizeof(htab_t ) );

		if (newTab == NULL)
			return NULL;
	
		for (unsigned int i = 0; i < size; i++)
			{
				newTab->ptr[i] = NULL;
			}

		newTab->htab_size = size;
		newTab->n = 0;
		newTab->hash_fun_ptr = hashfunction;
		return newTab;
	}
