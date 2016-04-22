#include "htable.h"

htab_t *htab_init(unsigned int size)
	{
		htab_t *newTab = malloc( size * sizeof( struct htab_listitem *) + sizeof( htab_t ));
		if ( newTab = NULL)
			return NULL;

		for ( unsigned int k = 0; k < size; k++)
			newTab->ptr[k] = NULL;
		
		newTab->htab_size = size;
		newTab->n = 0;
		newTab->hash_fun_ptr = hash_function;
	
		return newTab;	
	}
