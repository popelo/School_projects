#include "htable"

 struct htab_listitem *htab_lookup_add( htab_t *t, const char *key )
	{
		if ( t == NULL || key == NULL )
			{
				fprintf( stderr, "%s\n", "Invalid table or key" );
				return NULL;
			}
		
		unsigned int hash_idx = t->hash_fun_ptr(key, t->htab_size);
		struct h
	}
